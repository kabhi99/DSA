#!/usr/bin/env python3
"""
Post-process converted .md files to fix:
1. *...* italic wrapping from broken ═══ header detection
2. Code blocks not in ``` fences (code at column 0 after ──── lines)
3. Fragmented code fences (partial fencing of code blocks)
"""

import os
import re
import sys

EQUALS_PAT = re.compile(r'^\s*[=═]{10,}\s*$')
DASH_PAT = re.compile(r'^\s*[─━\-]{10,}\s*$')

CODE_START_RE = re.compile(
    r'^(int |long |void |bool |string |char |float |double |auto |'
    r'vector|unordered_|map<|set<|pair<|stack<|queue<|deque<|priority_queue<|'
    r'ListNode|TreeNode|Node |'
    r'while \(|for \(|if \(|else \{|else if|switch \(|'
    r'return |break;|continue;|'
    r'class |struct |enum |typedef |using |template|'
    r'#include|#define|'
    r'public |private |protected |static |final |'
    r'def |print\(|'
    r'sort\(|reverse\(|swap\(|push_back|emplace|insert\(|erase\(|'
    r'cin|cout|printf|scanf|'
    r'try \{|catch \(|throw |'
    r'const |unsigned |signed |size_t|'
    r'[a-zA-Z_]+\[|'  # array access
    r'[a-zA-Z_]+\()',  # function calls
    re.MULTILINE
)

BRACE_LINE_RE = re.compile(r'^[\s]*[{}][\s;]*$')
SEMICOLON_END = re.compile(r'.*;[\s]*$')
COMMENT_LINE = re.compile(r'^\s*//')
ASSIGNMENT_RE = re.compile(r'^[a-zA-Z_]\w*(\[.*\])?\s*[+\-*/]?=\s*')
ARROW_OP = re.compile(r'^[a-zA-Z_].*->|^[a-zA-Z_].*\.')


def is_code_line(line):
    """Check if a line looks like C++/Java code."""
    s = line.strip()
    if not s:
        return False
    if CODE_START_RE.match(s):
        return True
    if BRACE_LINE_RE.match(s):
        return True
    if SEMICOLON_END.match(s):
        return True
    if COMMENT_LINE.match(s):
        return True
    if ASSIGNMENT_RE.match(s):
        return True
    if s.startswith('//'):
        return True
    if s in ('{', '}', '};', '});'):
        return True
    return False


def is_definitely_not_code(line):
    """Check if a line is definitely text, not code."""
    s = line.strip()
    if not s:
        return False
    if s.startswith('#'):
        return True
    if s.startswith('**') and s.endswith('**'):
        return True
    if s.startswith('- ') or s.startswith('* '):
        return True
    if re.match(r'^[A-Z][A-Z\s&/\-,()]+:\s*$', s):
        return True
    if re.match(r'^\d+\.\s', s):
        return True
    if s.startswith('> '):
        return True
    return False


def fix_star_wrapping(lines):
    """Remove *...* italic wrapping from lines that shouldn't be italic."""
    result = []
    i = 0
    n = len(lines)

    while i < n:
        line = lines[i]
        stripped = line.strip()

        # Match broken header: ## followed by only dashes/equals
        if re.match(r'^## [-=]{10,}\s*$', stripped):
            i += 1
            continue

        # Match ***bold-italic*** that should be ### header
        m = re.match(r'^\*\*\*(.+)\*\*\*$', stripped)
        if m:
            result.append(f'### {m.group(1)}')
            i += 1
            continue

        # Match ** text* bullet pattern (was • text inside *...* block)
        m = re.match(r'^\*\*\s(.+)\*$', stripped)
        if m:
            result.append(f'- {m.group(1)}')
            i += 1
            continue

        # Match *...* wrapped lines (single italic)
        if re.match(r'^\*[^*]', line) and line.rstrip().endswith('*') and not line.rstrip().endswith('**'):
            inner = line.strip()[1:-1]

            # *----...----* → skip (separator line)
            if re.match(r'^[-=]{10,}$', inner.strip()):
                i += 1
                continue

            result.append(inner)
            i += 1
            continue

        result.append(line)
        i += 1

    return result


def fix_code_fences(lines):
    """Detect unfenced code and wrap in ``` blocks. Also merge fragmented fences."""
    result = []
    i = 0
    n = len(lines)

    while i < n:
        line = lines[i]

        # Already inside a code fence - pass through
        if line.strip().startswith('```'):
            result.append(line)
            i += 1
            # Pass through until closing ```
            while i < n and not lines[i].strip().startswith('```'):
                result.append(lines[i])
                i += 1
            if i < n:
                result.append(lines[i])
                i += 1
            continue

        # Check if this line is unfenced code
        if is_code_line(line) and not is_definitely_not_code(line):
            # Collect consecutive code lines
            code_block = []
            while i < n:
                l = lines[i]
                s = l.strip()

                if s.startswith('```'):
                    # Merge with existing fence
                    i += 1  # skip opening ```
                    while i < n and not lines[i].strip().startswith('```'):
                        code_block.append(lines[i])
                        i += 1
                    if i < n:
                        i += 1  # skip closing ```
                    continue

                if not s:
                    # Blank line - check if code continues after
                    j = i + 1
                    while j < n and not lines[j].strip():
                        j += 1
                    if j < n and is_code_line(lines[j]) and not is_definitely_not_code(lines[j]):
                        code_block.append(l)
                        i += 1
                    else:
                        break
                elif is_code_line(l) and not is_definitely_not_code(l):
                    code_block.append(l)
                    i += 1
                else:
                    break

            # Emit the code block
            if code_block:
                # Detect language
                lang = detect_code_lang(code_block)
                result.append(f'```{lang}')
                result.extend(code_block)
                result.append('```')
                result.append('')
            continue

        result.append(line)
        i += 1

    return result


def detect_code_lang(code_lines):
    """Detect programming language from code lines."""
    for l in code_lines:
        s = l.strip()
        if s.startswith('#include') or 'vector<' in s or 'cout' in s or 'cin' in s:
            return 'cpp'
        if s.startswith('public ') or s.startswith('private ') or s.startswith('class '):
            if 'self' not in s:
                return 'java'
        if s.startswith('def ') or s.startswith('print('):
            return 'python'
    for l in code_lines:
        s = l.strip()
        if '::' in s or '->' in s or s.startswith('auto ') or 'push_back' in s:
            return 'cpp'
    return ''


def fix_empty_headers(lines):
    """Fix headers that are just separators or braces like ### ────────, ### }."""
    result = []
    for line in lines:
        stripped = line.strip()
        # Headers that are just separator lines
        if re.match(r'^(#{1,3})\s+[-=─━]{5,}\s*$', stripped):
            continue
        # Headers that are just braces (from } before ──── lines)
        if re.match(r'^###?\s*[{};\s]+$', stripped):
            # Extract the brace content and add as plain code
            brace = re.sub(r'^#+\s*', '', stripped).strip()
            if brace:
                result.append(brace)
            continue
        result.append(line)
    return result


def clean_multiple_blanks(lines):
    """Remove consecutive blank lines (keep max 1)."""
    result = []
    prev_blank = False
    for line in lines:
        if not line.strip():
            if not prev_blank:
                result.append(line)
            prev_blank = True
        else:
            result.append(line)
            prev_blank = False
    return result


def process_file(path):
    """Process a single .md file."""
    with open(path, 'r') as f:
        content = f.read()

    lines = content.split('\n')

    # Step 1: Fix *...* wrapping
    lines = fix_star_wrapping(lines)

    # Step 2: Fix empty separator headers
    lines = fix_empty_headers(lines)

    # Step 3: Fix code fences
    lines = fix_code_fences(lines)

    # Step 4: Clean up multiple blank lines
    lines = clean_multiple_blanks(lines)

    result = '\n'.join(lines)

    with open(path, 'w') as f:
        f.write(result)


def main():
    dirs = sys.argv[1:] if len(sys.argv) > 1 else ['notes/md', 'Problems/md']
    for d in dirs:
        if not os.path.isdir(d):
            continue
        for root, _, files in os.walk(d):
            for f in sorted(files):
                if not f.endswith('.md'):
                    continue
                path = os.path.join(root, f)
                print(f'  Fixing: {f}')
                process_file(path)
    print('\nDone!')


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
# _*_ coding: utf-8 _*_

"""
author : xiaohai
email : xiaohaijin@outlook.com
"""


import subprocess


def main():
    subprocess.call(('make', 'clean'))
    subprocess.call(('xelatex', 'learnQt.tex'))
    subprocess.call(('bibtex',  'learnQt.aux'))
    subprocess.call(('xelatex', 'learnQt.tex'))
    subprocess.call(('xelatex', 'learnQt.tex'))
    subprocess.call(('evince',  'learnQt.pdf'))

if __name__ == '__main__':
    main()

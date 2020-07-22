\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{cal}
\LoadClass{bookauthor}

\usepackage{import}
\usepackage{standalone}
\usepackage[english]{babel}
\usepackage[yyyymmdd,hhmmss]{datetime}
\renewcommand{\dateseparator}{-}

% Tables with colored cells
\usepackage[table,dvipsnames]{xcolor}%
\definecolor{visitedcolor}{gray}{0.75}
\definecolor{activecolor}{gray}{0.40}
\newcommand\greencheckmark{{\color{ForestGreen}\checkmark}}

\RequirePackage{basiclistings}
\RequirePackage{dirtree}
\RequirePackage{email}
\RequirePackage{exam}
\RequirePackage{secondpage}
\RequirePackage{theorems}
% Graphics and images
\usepackage{tikz-qtree}
\usepackage{tikz}
\usetikzlibrary{automata, positioning, arrows}
% Encodings (to render letters with diacritics and special characters)
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{textcomp, eurosym}
\let\texteuro\euro
\newcommand\eqeuro{\text{\euro}}
% Pseudocode
\usepackage{algorithm}
\usepackage[noend]{algpseudocode}
% Tables that can span across multiple pages
\usepackage{longtable}
% Tables with diagonal slashes
\usepackage{diagbox}
% Tables with p centered
\usepackage{array}
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
% Math stuff
\usepackage[mathscr]{euscript}
\usepackage{amssymb}
\usepackage[inline]{enumitem}
\usepackage[binary-units=true]{siunitx} %SI units
\newcommand\comb[2]{^{#1}C_{#2}}
\usepackage{mathtools} %dcases
\newcommand\realset{\mathbb{R}}

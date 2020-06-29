\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{cal}
\LoadClass[a4paper]{book}
% Margins
\usepackage[top=35mm,bottom=35mm,left=25mm,right=25mm]{geometry}
% Tables with colored cells
\usepackage[table,dvipsnames]{xcolor}%
% Graphics and images
\usepackage{graphicx}
\usepackage{tikz}
\usepackage{tikz-qtree}
\usetikzlibrary{automata, positioning, arrows}
% Encodings (to render letters with diacritics and special characters)
\usepackage[utf8]{inputenc}
\DeclareUnicodeCharacter{2205}{$\emptyset$}
% Language
\usepackage[english]{babel}
%
% Hyperreferences
\usepackage{hyperref}
% Source code
\usepackage{listings}
\renewcommand{\lstlistingname}{File}
\lstset{
    basicstyle=\ttfamily,
    frame=tb, % draw frame at top and bottom of the code
    tabsize=4, % tab space width
    numbers=left, % display line numbers on the left
	% showstringspaces=false, % don't mark spaces in strings    
    commentstyle=\color{green}, % comment color
    keywordstyle=\color{blue}, % keyword color
    stringstyle=\color{red} % string color
}
\lstdefinelanguage{Maxima}{
	keywords={log,jacobian,determinant,subst,float,exp,diff,plot2d,matrix,invert},
	sensitive=true,
	comment=[n][\itshape]{/*}{*/}
}
% Pseudocode
\usepackage{algorithm}
\usepackage[noend]{algpseudocode}
% Tables with bold rows
\usepackage{tabularx}
\newcommand\setrow[1]{\gdef\rowmac{#1}#1\ignorespaces}
\newcommand\clearrow{\global\let\rowmac\relax}
\clearrow
% Tables that can span across multiple pages
\usepackage{longtable}
% Tables with diagonal slashes
%\usepackage{slashbox}
\usepackage{diagbox}
% Tables with p centered
\usepackage{array}
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
% Math stuff
\usepackage[mathscr]{euscript}
\usepackage{amsmath,amssymb}
\usepackage{mathtools}
\usepackage[inline]{enumitem}
\usepackage[binary-units=true]{siunitx} %SI units
\newcommand\comb[2]{^{#1}C_{#2}}
\usepackage{mathtools} %dcases
% Definitions, theorems, remarks,...
\usepackage{amsthm}
\usepackage{amssymb, latexsym} %Load math symbols like \blacksquare, but also load normal \leadsto arrows
\newtheorem{definition}{Definition}[section]
\newtheorem{theorem}{Theorem}[section]
\newtheorem{corollary}{Corollary}[theorem]
\newtheorem{lemma}[theorem]{Lemma}
\renewcommand\qedsymbol{$\blacksquare$}
\theoremstyle{remark}
\newtheorem*{remark}{Remark}
% Some work
\def\title#1{\gdef\@title{#1}\gdef\@@title{#1}}
\def\author#1{\gdef\@author{#1}\gdef\@@author{#1}}
\let\@@title\@empty
\let\@@author\@empty
% Headers and footers
\RequirePackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}
\fancyhead[RE, LO]{\textit{\leftmark}}
\fancyhead[LE, RO]{\thepage}
\fancyfoot[LE, RO]{\ifx\@@author\@empty\else\@@author\fi}
% Directory trees
\RequirePackage{dirtree}
% Answer separator
\newcommand\ansseparator{\noindent\hfil\rule{0.5\textwidth}{.4pt}\hfil}
% Alias
\setcounter{secnumdepth}{1}
\newcommand\exam[1]{\chapter{#1}}
\newcommand\exampart[1]{\section{#1}}
\newcommand\question[1]{\subsection{#1}}
\newcommand\questionitem[1]{\subsubsection{#1}}
\makeatletter
\renewcommand\thesection{\thechapter\ifnum\c@section>\z@ -P\arabic{section}\fi}
\renewcommand\thesubsection{\thesection-\arabic{subsection}}
\renewcommand\thesubsubsection{\thesubsection\alph{subsubsection}}
\makeatother
\RequirePackage{titlesec}
\newcommand{\sectionbreak}{\clearpage}
% Tick
\newcommand\greencheckmark{{\color{ForestGreen}\checkmark}}
% Colors
\definecolor{visitedcolor}{gray}{0.75}
\definecolor{activecolor}{gray}{0.40}


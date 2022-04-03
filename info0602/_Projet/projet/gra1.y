\documentclass[12pt,a4paper]{article}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\usepackage[french]{babel}

\usepackage{listings}

\usepackage{tikz}
\usetikzlibrary{automata, positioning, arrows}

\tikzset{
  ->,
  >=stealth',
  node distance=3cm,
  every state/.style={thick, fill=gray!10},
  initial text=$ $,
}

%**************************************************************************************************
% *
% * Configuration des marges
% *
%**************************************************************************************************

\usepackage{calc}
\newcommand{\marges}[2]{
  \newlength{\HEADHEIGHT}
  \setlength{\HEADHEIGHT}{28cm-#1}
  \setlength{\HEADHEIGHT}{\HEADHEIGHT/2}
  
  \newlength{\MARGIN}
  \setlength{\MARGIN}{16cm-#2}
  \setlength{\MARGIN}{\MARGIN/2}
    
	\topmargin -2.5cm
	\headheight \HEADHEIGHT
	\headsep 0.75cm
	\topskip 0cm 
	\textheight #1
	\textwidth #2
	\oddsidemargin \MARGIN
	\evensidemargin \MARGIN
	\parindent 0.5cm
	\parskip 0.75em plus 0.2em minus 0.1em
}

\marges{26cm}{18cm}

%**************************************************************************************************
% *
% * Début du document
% *
%**************************************************************************************************

\begin{document}
\noindent Le contenu du fichier .aut :
\begin{lstlisting}[mathescape,frame=single]
GRAMMAIRE
T={a,b,c,d,e}
N={S,A,B}
R={
(S
->
a
A
B
e)
(A
->
A
b
c
|
b)
(B
->
d)
}
S=S
\end{lstlisting}
Ce qui donne l'automate suivant :
\begin{figure}[ht]
  \centering
  \begin{tikzpicture})
\node[state, right of=q-1] (q0) {$q_0$};
\node[state, right of=q0] (q1) {$q_1$};
\node[state, right of=q1] (q2) {$q_2$};
\draw
(q ) edge[bend left, above] node{�} (q )
(q ) edge[bend left, above] node{ } (q )
(q ) edge[bend left, above] node{�} (q );
  \end{tikzpicture}
  \caption{Automate}
\end{figure}
\end{document}
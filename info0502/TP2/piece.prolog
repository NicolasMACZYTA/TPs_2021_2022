oppose(pile,face).
oppose(face,pile).
transition(P1,P2,P3,P4,P5,P3):-oppose(P1,P4),oppose(P2,P5).
transition(P1,P2,P3,P1,P5,P6):-oppose(P2,P5),oppose(P3,P6).
transition(P1,P2,P3,P4,P2,P6):-oppose(P1,P4),oppose(P3,P6).
jeuPiece(P1,P2,P3):-jeuPiece(P1,P2,P3,_,_,_).
jeuPiece(P1,P2,P3,V,V,V):-transition(P1,P2,P3,Q1,Q2,Q3),transition(Q1,Q2,Q3,R1,R2,R3),transition(R1,R2,R3,V,V,V),affichePiece(P1,P2,P3),affichePiece(Q1,Q2,Q3),affichePiece(R1,R2,R3),affichePiece(V,V,V).
affichePiece(P1,P2,P3):-format('~a ~a ~a ~n',[P1,P2,P3]).
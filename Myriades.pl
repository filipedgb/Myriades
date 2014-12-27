/*PLOG MIEIC 2014*/
/* Andre Pires ei12058 */
/* Filipe Gama ei12068 */

:- use_module(library(lists)).
:- use_module(library(random)).
:- use_module(library(system)).

/* INICIALIZACAO DO TABULEIRO VAZIO */
/* N = tamanho */
initRow(N,R):- initRow(N,[],R).
initRow(0,R,R).
initRow(N,R1,R):- 
			N > 0,
			N1 is N-1,
			initRow(N1,[""|R1],R).

initBoard(0,_,B,B).
initBoard(N,R,B1,B):-
			N > 0,
			N1 is N-1,
			initBoard(N1,R,[R|B1],B).

initBoard(B,N):- initRow(N,R), initBoard(N,R,[],B).

/* P = peca, R:row e C:column coordenadas, B:lista*/
/*Adicionar uma peca*/
addPiece(P,R,C,B,B1):-
			piece(P),				/*verifica se a peca inserida e valida*/
			isEmpty(R,C,B),			/*verifica se o lugar esta vazio*/
			(\+ existsInBoard(P,B); /*nao pode adicionar pecas repetidas,*/
			isGrey(P)), 			/*a nao ser que seja cinzenta*/
			nth0(R,B,R1),
			addPiece(C,P,R1,R2),
			addPiece(R,R2,B,B1).

addPiece(N,P,B,B2):- 
			length(B1,N),
			append(B1, [_|R],B),
			append(B1,[P|R],B2).

/*Remove Piece -> adicionando um espaço vazio no lugar dela*/
removePiece(R,C,B,B1):-
			isPiece(R,C,B),	
			nth0(R,B,R1),
			addPiece(C,"",R1,R2),
			addPiece(R,R2,B,B1).

/*R,C - row column (onde esta a peca) // R1,C1 - row column (sitio onde meter a peca)*/
/*move uma peca*/
movePiece(R,C,R1,C1,B,B1):- 
			isPiece(R,C,B),
			getPiece(R,C,B,P),
			\+ isGrey(P),
			isEmpty(R1,C1,B),
			noPieceBetween(R,C,R1,C1,B),
			removePiece(R,C,B,B2),
			addPiece(P,R1,C1,B2,B1).

/*para quando ha adjacentes do adversario com menor valor, remove a peca do local, e adiciona a peca cinzenta*/
changePiece(R,C,B,B1):-
			removePiece(R,C,B,B2),
			addPiece([g,0],R,C,B2,B1).

/*verifica se ha uma peca entre a posicao da peca e o sitio que a quer mover*/
/* true - nao ha peca, false - ha peca*/
noPieceBetween(R,C,R1,C1,B):-
	noPieceBetweenH(R,C,R1,C1,B);
	noPieceBetweenV(R,C,R1,C1,B);
	noPieceBetweenO(R,C,R1,C1,B).

/*HORIZONTAL*/
noPieceBetweenH(R,C,R,C,_).
noPieceBetweenH(R,C,R,C1,B):- 
		C < C1,
		C2 is C + 1,
		isEmpty(R,C2,B),
		noPieceBetweenH(R,C2,R,C1,B).

noPieceBetweenH(R,C,R,C1,B):- 
		C > C1,
		C2 is C - 1,
		isEmpty(R,C2,B),
		noPieceBetweenH(R,C2,R,C1,B).

/*VERTICAL*/
noPieceBetweenV(R,C,R,C,_).
noPieceBetweenV(R,C,R1,C,B):- 
		R < R1,
		R2 is R + 1,
		isEmpty(R2,C,B),
		noPieceBetweenV(R2,C,R1,C,B).

noPieceBetweenV(R,C,R1,C,B):- 
		R > R1,
		R2 is R - 1,
		isEmpty(R2,C,B),
		noPieceBetweenV(R2,C,R1,C,B).

/*OBLIQUO*/	
noPieceBetweenO(R,C,R,C,_).
/* -> ^ : direita cima */
noPieceBetweenO(R,C,R1,C1,B):-
		R1 < R, C1 > C,
		R2 is R-1, C2 is C+1,
		isEmpty(R2,C2,B),
		noPieceBetweenO(R2,C2,R1,C1,B).

/* -> v : direita baixo */
noPieceBetweenO(R,C,R1,C1,B):-
		R1 > R, C1 > C,
		R2 is R+1, C2 is C+1,
		isEmpty(R2,C2,B),
		noPieceBetweenO(R2,C2,R1,C1,B).

/* <- ^ : esquerda cima */
noPieceBetweenO(R,C,R1,C1,B):-
		R1 < R, C1 < C,
		R2 is R-1, C2 is C-1,
		isEmpty(R2,C2,B),
		noPieceBetweenO(R2,C2,R1,C1,B).

/* <- v : esquerda baixo */
noPieceBetweenO(R,C,R1,C1,B):-
		R1 > R, C1 < C,
		R2 is R1+1, C2 is C-1,
		isEmpty(R2,C2,B),
		noPieceBetweenO(R2,C2,R1,C1,B).

/*ADJACENTES*/
/*retorna lista com todas as pecas adjacentes*/
/*extremo esquerdo cima*/
getadjacentes(0,0,B,L):- !,
		R1 is 1,
		C1 is 1,
		getPiece(R1,0,B,P0),
		getPiece(0,C1,B,P2),
		getPiece(R1,C1,B,P4),

		addToList([P0],[],L1),
		addToList([P2],L1,L3),
		addToList([P4],L3,L).

/*extremo cima*/
getadjacentes(0,C,B,L):- 
		C > 0,
		length(B,X),
		Buff is X-1,
		C < Buff,
		!,
		R1 is 1,
		C1 is C+1,
		C2 is C-1,
		getPiece(R1,C,B,P0),
		getPiece(0,C1,B,P2),
		getPiece(0,C2,B,P3),

		getPiece(R1,C1,B,P4),
		getPiece(R1,C2,B,P7),

		addToList([P0],[],L1),
		addToList([P2],L1,L3),
		addToList([P3],L3,L4),
		addToList([P4],L4,L5),
		addToList([P7],L5,L).

/*extremo esquerdo baixo*/
getadjacentes(R,0,B,L):- 
		R > 0,
		length(B,X),
		Buff is X-1,
		R = Buff,
		!,
		C1 is 1,
		R2 is R-1,
		getPiece(R2,0,B,P1),
		getPiece(R,C1,B,P2),
		getPiece(R2,C1,B,P6),

		addToList([P1],[],L1),
		addToList([P2],L1,L2),
		addToList([P6],L2,L).

/*extremo esquerdo*/
getadjacentes(R,0,B,L):- 
		R > 0,
		length(B,X),
		Buff is X-1,
		R < Buff,
		!,
		R1 is R+1,
		C1 is 1,
		R2 is R-1,
		getPiece(R1,0,B,P0),
		getPiece(R2,0,B,P1),
		getPiece(R,C1,B,P2),

		getPiece(R1,C1,B,P4),
		getPiece(R2,C1,B,P6),

		addToList([P0],[],L1),
		addToList([P1],L1,L2),
		addToList([P2],L2,L3),
		addToList([P4],L3,L5),
		addToList([P6],L5,L).

/*extremo direito cima*/
getadjacentes(0,C,B,L):- 
		C > 0,
		length(B,X),
		Buff is X-1,
		C = Buff,
		!,
		R1 is 1,
		C1 is C-1,
		getPiece(R1,C,B,P1),
		getPiece(0,C1,B,P3),
		getPiece(R1,C1,B,P5),

		addToList([P1],[],L2),
		addToList([P3],L2,L4),
		addToList([P5],L4,L).

/*extremo direito baixo*/
getadjacentes(R,C,B,L):- 
		R > 0, C > 0,
		length(B,X),
		Buff is X-1,
		R = Buff, C = Buff,
		!,
		R1 is R-1,
		C1 is C-1,
		getPiece(R1,C,B,P1),
		getPiece(R,C1,B,P3),
		getPiece(R1,C1,B,P5),

		addToList([P1],[],L2),
		addToList([P3],L2,L4),
		addToList([P5],L4,L).

/*extremo baixo*/
getadjacentes(R,C,B,L):- 
		R > 0, C > 0,
		length(B,X),
		Buff is X-1,
		R = Buff, C < Buff,
		!,
		R1 is R-1,
		C1 is C+1,
		C2 is C-1,
		getPiece(R1,C,B,P1),
		getPiece(R,C1,B,P2),
		getPiece(R,C2,B,P3),

		getPiece(R1,C2,B,P5),
		getPiece(R1,C1,B,P6),

		addToList([P1],[],L2),
		addToList([P2],L2,L3),
		addToList([P3],L3,L4),
		addToList([P5],L4,L6),
		addToList([P6],L6,L).

/*extremo direito*/
getadjacentes(R,C,B,L):- 
		R > 0, C > 0,
		length(B,X),
		Buff is X-1,
		R < Buff, C = Buff,
		!,
		R1 is R-1,
		R2 is R+1,
		C1 is C-1,
		getPiece(R2,C,B,P0),
		getPiece(R1,C,B,P1),
		getPiece(R,C1,B,P3),

		getPiece(R1,C1,B,P5),
		getPiece(R2,C1,B,P7),

		addToList([P0],[],L1),
		addToList([P1],L1,L2),
		addToList([P3],L2,L4),
		addToList([P5],L4,L6),
		addToList([P7],L6,L).

/*meio*/
getadjacentes(R,C,B,L):- 
		R > 0, C > 0,
		length(B,X),
		Buff is X-1,
		R < Buff, C < Buff,
		!,
		R1 is R+1,
		R2 is R-1,
		C1 is C+1,
		C2 is C-1,
		getPiece(R1,C,B,P0),
		getPiece(R2,C,B,P1),
		getPiece(R,C1,B,P2),
		getPiece(R,C2,B,P3),

		getPiece(R1,C1,B,P4),
		getPiece(R2,C2,B,P5),
		getPiece(R2,C1,B,P6),
		getPiece(R1,C2,B,P7),

		addToList([P0],[],L1),
		addToList([P1],L1,L2),
		addToList([P2],L2,L3),
		addToList([P3],L3,L4),
		addToList([P4],L4,L5),
		addToList([P5],L5,L6),
		addToList([P6],L6,L7),
		addToList([P7],L7,L).

addToList([P],L,L1):- 
		piece(P),
		append(L,[P],L1).

addToList(_,L,L).

/*retorna em N, o num de pecas adversarias com menor valor*/
adjacentes(R,C,B,N):-
		getPiece(R,C,B,P),
		(
		isWhite(P), !,
			getadjacentes(R,C,B,L),
			adjAuxW(P,L,0,N);

		isBlack(P), !,
			getadjacentes(R,C,B,L),
			adjAuxB(P,L,0,N)
		).

/* adjacentes que sao pretas*/
adjAuxW(_,[],N,N).
adjAuxW(P,[H|T],Acc,N):-
		isBlack(H),
		getValue(P,V1),
		getValue(H,V2),
		V1 > V2,
		Acc1 is Acc+1,
		adjAuxW(P,T,Acc1,N);
		adjAuxW(P,T,Acc,N).

/* adjacentes que sao brancas*/
adjAuxB(_,[],N,N).
adjAuxB(P,[H|T],Acc,N):-
		isWhite(H),
		getValue(P,V1),
		getValue(H,V2),
		V1 > V2,
		Acc1 is Acc+1,
		adjAuxB(P,T,Acc1,N);
		adjAuxB(P,T,Acc,N).

/*PIECE FUNCS*/
color(b). /*black*/
color(w). /*white*/
color(g). /*grey*/

isWhite([H|_]):- color(H), H=w.
isBlack([H|_]):- color(H), H=b.
isGrey([H|_]):- color(H), H=g.

getValue([H|T],N):- piece([H|T]), N is T.

getPiece(R,C,B,P):-
			nth0(R,B,R1),
			nth0(C,R1,P).

isPiece(R,C,B):- 
			getPiece(R,C,B,P),
			piece(P).


piece([Color,Value]):-
			color(Color),
			Value > -1,
			Value < 50.

isEmpty(R,C,B):- \+ isPiece(R,C,B).


/* escolhe uma posicao vazia aleatoriamente*/
findRandEmpty(B,R,C):- findEmpty(B,Cs), findRandAux(Cs,R,C).

/* encontra todas as posicoes vazias */
findEmpty(B,Cs):- length(B,X), findEmpty(B,X,[],Cs).

findEmpty(_,0,Cs,Cs).
findEmpty(B,R,Acc,Cs):-
	R1 is R-1,
	findall(C, (getPiece(R1,C,B,P), \+ piece(P)),Cs1),
	length(Cs1, L),
	(
		L > 0,
		findEmpty(B,R1,[[R1,Cs1]|Acc],Cs);

		findEmpty(B,R1,Acc,Cs)
	).

/* escolhe uma posicao duma peca aleatoriamente consoante a cor*/
findRandColor(B,R,C,Cor):- findColor(B,Cor,Cs), findRandAux(Cs,R,C).

/* encontra todas as pecas da cor fornecida*/
findColor(B,Cor,Cs):- length(B,X),(Cor = w, findColorW(B,X,[],Cs); Cor = b, findColorB(B,X,[],Cs)).
findColorW(_,0,Cs,Cs).
findColorW(B,R,Acc,Cs):-
	R1 is R-1,
	findall(C, (getPiece(R1,C,B,P), isWhite(P)),Cs1),
	length(Cs1, L),
	(
		L > 0,
		findColorW(B,R1,[[R1,Cs1]|Acc],Cs);

		findColorW(B,R1,Acc,Cs)
	).

findColorB(_,0,Cs,Cs).
findColorB(B,R,Acc,Cs):-
	R1 is R-1,
	findall(C, (getPiece(R1,C,B,P), isBlack(P)),Cs1),
	length(Cs1, L),
	(
		L > 0,
		findColorB(B,R1,[[R1,Cs1]|Acc],Cs);

		findColorB(B,R1,Acc,Cs)
	).

findRandAux(Cs,R,C):- /* Cs = [[R0,[C1,C2,...]], [R1,[C1,C2,...]],...]*/
		length(Cs,N),
		random(0,N,Y),
		nth0(Y,Cs,Cs1),
		nth0(0,Cs1,R),
		nth0(1,Cs1,T),
		length(T,X), 
		X > 0, !,
		random(0,X,C1),
		nth0(C1,T,C).

/* Verifica se a peca (P) existe no board*/
existsInBoard(P,[H|_]):-
			member(P,H),
			!.

existsInBoard(P,[_|T]):-
			existsInBoard(P,T).


/* Verifica se tabuleiro esta cheio*/
isFull(_,0).
isFull(B,R):-
		R > 0,
		R1 is R - 1,
		isPiece(R1,B),
		isFull(B,R1).

isFull([]).
isFull([H|T]):- 
		length(H,N),
		isFull(H,N),
		isFull(T).

/* usado para auxiliar funcao anterior*/
isPiece(R,B):-
		nth0(R,B,P),
		piece(P).


/*SOMA DAS PRETAS*/
addBlack([H|T],S,N):-
		isBlack([H|T]),
		N is S + T,
		!.
addBlack(_,S,S).

sumOfBlackRow([],Acc,Acc).
sumOfBlackRow([H|T],Acc,N):-
		addBlack(H,Acc,S),
		sumOfBlackRow(T,S,N).

sumOfBlack([],Sum,Sum).
sumOfBlack([H|T],Acc,Sum):-
		sumOfBlackRow(H,0,N),
		S is Acc + N,
		sumOfBlack(T,S,Sum).

sumOfBlack(B,Sum):-sumOfBlack(B,0,Sum).

/*SOMA DAS BRANCAS*/
addWhite([H|T],S,N):-
		isWhite([H|T]),
		N is S + T,
		!.
addWhite(_,S,S).

sumOfWhiteRow([],Acc,Acc).
sumOfWhiteRow([H|T],Acc,N):-
		addWhite(H,Acc,S),
		sumOfWhiteRow(T,S,N).

sumOfWhite([],Sum,Sum).
sumOfWhite([H|T],Acc,Sum):-
		sumOfWhiteRow(H,0,N),
		S is Acc + N,
		sumOfWhite(T,S,Sum).

sumOfWhite(B,Sum):-sumOfWhite(B,0,Sum).


/*Escreve no ecra o vencedor atual*/
winner(B):- sumOfBlack(B,Sb),
			sumOfWhite(B,Sw), 
			(
			(Sb < Sw,
				write('*******************************************************'), nl,
        		write('*******************************************************'), nl,
                write('***                                                 ***'), nl,
                write('***            WINNER IS PLAYER 1 !!!!!!            ***'), nl,
                write('***                                                 ***'), nl,
                write('***                 CONGRATULATIONS                 ***'), nl,
                write('***                                                 ***'), nl,
                write('*******************************************************'), nl,
        		write('*******************************************************'), nl );
			(Sb > Sw,
				write('*******************************************************'), nl,
        		write('*******************************************************'), nl,
                write('***                                                 ***'), nl,
                write('***            WINNER IS PLAYER 2 !!!!!!            ***'), nl,
                write('***                                                 ***'), nl,
                write('***                 CONGRATULATIONS                 ***'), nl,
                write('***                                                 ***'), nl,
                write('*******************************************************'), nl,
        		write('*******************************************************'), nl );
			(Sb = Sw,
				write('*******************************************************'), nl,
        		write('*******************************************************'), nl,
                write('***                                                 ***'), nl,
                write('***                 IT IS A DRAW!                   ***'), nl,
                write('***                                                 ***'), nl,
                write('***            YOU SHOULD PLAY AGAIN :)             ***'), nl,
                write('***                                                 ***'), nl,
                write('*******************************************************'), nl,
        		write('*******************************************************'), nl
        	)), pause.
				

/* Jogo termina quando o tabuleiro esta cheio, de seguida imprime o tabuleiro e o respetivo vencedor*/
endOfGame(B):- isFull(B), printboard(B), winner(B).

/*------------------------------------- IA --------------------------------------------------*/

/* Função que procura primeira peça a partir de R0 e C0, daquela cor, e guarda as suas coordenadas em RF e CF */
findFirstPiece(Board,R0,C0,RF,CF,Color) :- 
			isPiece(R0,C0,Board), getPiece(R0,C0,Board,Piece), 
			(Color = w, isWhite(Piece); Color = b, isBlack(Piece)),
			RF = R0, CF = C0.

findFirstPiece(Board,R0,C0,RF,CF,Color) :- 
		length(Board,Boardsize),
		(
			(C1 is C0 + 1, C1 < Boardsize, findFirstPiece(Board,R0,C1,RF,CF,Color));
			(C1 is 0, R1 is R0 + 1, R1 < Boardsize, findFirstPiece(Board,R1,C1,RF,CF,Color));
			RF is -1, CF is -1
		).

/* Decide o melhor movimento a fazer (pelo pc) */
decideMove(Board,Cor,NewBoard):- decideMoveAux(Board,NewBoard,Cor,0,0).
decideMoveAux(Board,Board,_,-1,_).
decideMoveAux(Board,Board,_,_,-1).
decideMoveAux(Board,NewBoard,Cor,Ri,Ci):- 
  		findFirstPiece(Board,Ri,Ci,RF,CF,Cor),
  		(
   			(
    			RF > -1, CF > -1, 
    			((
    			((Cor=b, findVulnerable(RF,CF,Board,RVictim,CVictim,w)); (Cor=w, findVulnerable(RF,CF,Board,RVictim,CVictim,b))), 
    				RVictim > -1, CVictim > -1, 
    					write('PC moved piece from ('), write(RF), write(','), write(CF), write(') to ('), write(RVictim), write(','),write(CVictim), write(')'), nl,
    					movePiece(RF,CF,RVictim,CVictim,Board,B2), calculateConsequencesPC(B2,RVictim,CVictim,Cor,NewBoard)
    				);
    			(length(Board,CF), RF1 is RF+1, decideMoveAux(Board,NewBoard,Cor,RF1,0));
    			(CF1 is CF+1 , decideMoveAux(Board,NewBoard,Cor,RF,CF1)))
   			);
   			decideMoveAux(Board,NewBoard,Cor,-1,-1)
  		).

/* Encontra uma peca de menor valor ao alcance da peca fornecida*/
findVulnerable(R,C,B,RVictim,CVictim,Cor):-
		length(B,Boardsize),
		getPiece(R,C,B,P), getValue(P,Valor),
		(
			vulnerablePieceH(R,C,R,0,B,RVictim,CVictim,Cor,Valor);
			vulnerablePieceH(R,C,R,Boardsize,B,RVictim,CVictim,Cor,Valor);
			vulnerablePieceV(R,C,Boardsize,C,B,RVictim,CVictim,Cor,Valor);
			vulnerablePieceV(R,C,0,C,B,RVictim,CVictim,Cor,Valor);
			RVictim is -1, CVictim is -1
		).

/* HORIZONTAL */
vulnerablePieceH(R,C,R,C,_,_,_):- fail.
vulnerablePieceH(R,C,R,C1,B,RVictim,CVictim,Cor,Valor):- 
		( C < C1, C2 is C + 1, isEmpty(R,C2,B), vulnerablePieceH(R,C2,R,C1,B,RVictim,CVictim,Cor,Valor)); 
		( C < C1, C2 is C + 1, isPiece(R,C2,B),  getPiece(R,C2,B,P), Cor = w, isWhite(P), getValue(P,Valor2),Valor > Valor2, RVictim = R, C3 is C2-1, CVictim = C3);
		( C < C1, C2 is C + 1, isPiece(R,C2,B),  getPiece(R,C2,B,P), Cor = b, isBlack(P), getValue(P,Valor2), Valor > Valor2, RVictim = R, C3 is C2-1, CVictim = C3).

vulnerablePieceH(R,C,R,C1,B,RVictim,CVictim,Cor,Valor):- 
		( C > C1, C2 is C - 1, isEmpty(R,C2,B), vulnerablePieceH(R,C2,R,C1,B,RVictim,CVictim,Cor,Valor));
		( C > C1, C2 is C - 1, isPiece(R,C2,B),  getPiece(R,C2,B,P), Cor = w, isWhite(P), getValue(P,Valor2), Valor > Valor2, RVictim = R, C3 is C2+1, CVictim = C3);
		( C > C1, C2 is C - 1, isPiece(R,C2,B),  getPiece(R,C2,B,P), Cor = b, isBlack(P), getValue(P,Valor2), Valor > Valor2, RVictim = R, C3 is C2+1, CVictim = C3).


/*VERTICAL*/
vulnerablePieceV(R,C,R,C,_,_,_):- fail.
vulnerablePieceV(R,C,R1,C,B,RVictim,CVictim,Cor,Valor):- 
		(R < R1, R2 is R + 1, isEmpty(R2,C,B), vulnerablePieceV(R2,C,R1,C,B,RVictim,CVictim,Cor,Valor));
		(R < R1, R2 is R + 1, isPiece(R2,C,B), getPiece(R2,C,B,P), Cor = w, isWhite(P),  getValue(P,Valor2), Valor > Valor2, CVictim = C, R3 is R2-1, RVictim = R3);
		(R < R1, R2 is R + 1, isPiece(R2,C,B), getPiece(R2,C,B,P), Cor = b, isBlack(P),  getValue(P,Valor2), Valor > Valor2, CVictim = C, R3 is R2-1, RVictim = R3).

vulnerablePieceV(R,C,R1,C,B,RVictim,CVictim,Cor,Valor):- 
		(R > R1, R2 is R - 1, isEmpty(R2,C,B), vulnerablePieceV(R2,C,R1,C,B,RVictim,CVictim,Cor,Valor));
		(R > R1, R2 is R - 1, isPiece(R2,C,B), getPiece(R2,C,B,P), Cor = w, isWhite(P), getValue(P,Valor2), Valor > Valor2,  CVictim = C, R3 is R2+1, RVictim = R3);
		(R > R1, R2 is R - 1, isPiece(R2,C,B),  getPiece(R2,C,B,P), Cor = b, isBlack(P), getValue(P,Valor2), Valor > Valor2, CVictim = C, R3 is R2+1, RVictim = R3).


/*end ------------------------------------- IA --------------------------------------------------*/


/* Funcoes de INPUT/OUTPUT */

/* Funcoes com o objetivo de imprimir o tabuleiro*/
writeCell([]):- write('|    ').
writeCell(['g', _]):- write('| oo ').
writeCell(['w', Num]):- Num < 10, write('|<0'), write(Num), write('>').
writeCell(['w', Num]):- write('|<'), write(Num), write('>').
writeCell(['b', Num]):- Num < 10, write('|*0'), write(Num), write('*').
writeCell(['b', Num]):- write('|*'), write(Num), write('*').

printline([]) :- write('|     ').
printline([H|T]):- writeCell(H), printline(T).

calculateDiv(N,D):- N1 is (N*5)+1, calculateDiv(N1,"",D).
calculateDiv(0,D,D).
calculateDiv(N,R1,D):- 
		N > 0,
   		N1 is N-1,
   		calculateDiv(N1,['_'|R1],D).

writeColumnNumber(N,N).
writeColumnNumber(N,N1):- N2 is N+1, write('   '), write(N), write(' '), writeColumnNumber(N2,N1).

writeDiv([]).
writeDiv([H|T]):- write(H), writeDiv(T).

printboard(B,D,N):- printboardAux(B,N,D,0).
printboardAux([],_,D,_):- write('  '), writeDiv(D).
printboardAux([H | T], N, D, Nr):- write('  '), writeDiv(D), nl, nl, write(Nr), write(' '), printline(H), nl, N2 is Nr + 1, printboardAux(T,N,D,N2).

printboard(B):- length(B,N), write(' '), calculateDiv(N,D), writeColumnNumber(0,N), nl, printboard(B,D,N),nl,nl.


printPlayer(CorJogador) :- 	CorJogador = b, nl, nl, write('*PLAYER 1*'), nl;
							CorJogador = w, nl, nl, write('<PLAYER 2>'), nl.


printCurrentWinner(Board) :- nl, write('Game status:'), winner(Board).

cleanScreen :- nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl.

/* Funcoes para contar o numero de pecas */
numPieces(CorJogador,B,N):-
		CorJogador = b,
		numBlack(B,0,N);
		CorJogador = w,
		numWhite(B,0,N).

/* Pecas pretas */
addOneBlack([H|_],S,N):-
		isBlack([H|_]),
		N is S + 1,
		!.
addOneBlack(_,S,S).

numBlackRow([],Acc,Acc).
numBlackRow([H|T],Acc,N):-
		addOneBlack(H,Acc,S),
		numBlackRow(T,S,N).

numBlack([],Sum,Sum).
numBlack([H|T],Acc,Sum):-
		numBlackRow(H,0,N),
		S is Acc + N,
		numBlack(T,S,Sum).

/* Pecas brancas */
addOneWhite([H|_],S,N):-
		isWhite([H|_]),
		N is S + 1,
		!.
addOneWhite(_,N,N).

numWhiteRow([],Acc,Acc).
numWhiteRow([H|T],Acc,N):-
		addOneWhite(H,Acc,S),
		numWhiteRow(T,S,N).

numWhite([],Sum,Sum).
numWhite([H|T],Acc,Sum):-
		numWhiteRow(H,0,N),
		S is Acc + N,
		numWhite(T,S,Sum).


/*------------------------ HUMAN vs HUMAN -----------------------------------*/
/* Quando existem adjacentes de menor valor */
winsBattle(0,_,_,_,Board,Board). 
winsBattle(N,CorJogador,Row,Column,Board,BF) :- 
		numPieces(CorJogador,Board,Num),
		(
		Num > 1,
			winsBattleAux(CorJogador,Row,Column,Board,BF),
			BF \= -2,
			NF is N - 1,
			winsBattle(NF,CorJogador,Row,Column,BF,_);
		write('\nCant change more pieces\n'), 
		BF = Board
		).

winsBattleAux(CorJogador,Row,Column,Board,BF) :- 
		write('\nYou have a lower opponent piece adjacent to yours'),nl,
		write('Choose the piece you want to take out (except the one you moved)'),nl,
		write('Row: '), read(X),
		write('Column: '), read(Y),
		(
			(X = -1, write('Change canceled.'), nl, BF = Board);
			(X = -2, write('Change canceled, exiting...'), nl, BF is -2);
			CorJogador = w, getPiece(X,Y,Board,P), (Row \= X; Column \= Y), isWhite(P), changePiece(X,Y,Board,BF), cleanScreen, printboard(BF);
		 	CorJogador = b, getPiece(X,Y,Board,P), (Row \= X; Column \= Y), isBlack(P), changePiece(X,Y,Board,BF), cleanScreen, printboard(BF);
			(write('That piece is not yours so it cant be removed.'), nl, winsBattleAux(CorJogador,Row,Column,Board,BF))
		).

/* Calcula as consequencias do movimento duma peca */
calculateConsequences(Board,Row,Column,CorJogador,BF) :- 
		numPieces(CorJogador,Board,Num),
		Num > 1,
		adjacentes(Row,Column,Board,N),
	 	(
	 		N > 0,
	 		winsBattle(N,CorJogador,Row,Column,Board,BF);
			BF = Board
		);
		nl, write('Cant change pieces yet'), nl,
		BF = Board.

/* Jogar */
playerPlay(B,CorJogador):- 
		(B = -2, write('Exiting first...')); /* Jogador decidiu sair do jogo */
		nl,endOfGame(B);
		nl,printboard(B), nl, nl,
		printPlayer(CorJogador), nl,
		(
			(existsPiecesInBoard(B,CorJogador),
				write('Do you wish to move a piece? (1 for yes, other for no)'), nl,
				read(X),
				(	X = -2, 
						write('Exiting second...'), B2 is -2;
					X = 1, 
						playerMove(B,B1,CorJogador),
						(
							(B1 = -2, write('Exiting after move...'));
		 					playerAdd(B1,B2,CorJogador)
						);
					playerAdd(B,B2,CorJogador)
				)
			);
			write('Cant move pieces yet'),
			playerAdd(B,B2,CorJogador)
		),
		(CorJogador = b, playerPlay(B2,w); CorJogador = w, playerPlay(B2,b)).

/* Verifica se existem pecas do jogador "CorJogador" no tabuleiro*/
existsPiecesInBoard(Board, CorJogador):- existsInBoard([CorJogador,_],Board).

/* Mover uma peca */
playerMove(B,BF,CorJogador) :- 
		nl, write('Please choose the piece want to move, followed by its coords'), nl,
		write('Current row: '), read(X), nl,
		write('Current column: '), read(Y), nl,
		write('New row: '), read(NewX), nl,
		write('New column: '), read(NewY), nl,
		(
			((X = -1; Y = -1; NewX = -1; NewY = -1), write('Move canceled.'), nl, BF = B);
			((X = -2; Y = -2; NewX = -2; NewY = -2), write('Move canceled, exiting...'), nl, BF is -2);
			(CorJogador = b, getPiece(X,Y,B,P), isBlack(P), movePiece(X,Y,NewX,NewY,B,B2), cleanScreen, printboard(B2), calculateConsequences(B2,NewX,NewY,CorJogador,BF) );
			(CorJogador = w, getPiece(X,Y,B,P), isWhite(P), movePiece(X,Y,NewX,NewY,B,B2), cleanScreen, printboard(B2), calculateConsequences(B2,NewX,NewY,CorJogador,BF) );
			(write('That move is not valid'), playerMove(B,BF,CorJogador))
		). 

/* Adicionar uma peca */
playerAdd(B,B1,CorJogador) :- 
		nl, write('You must add a piece now.'), nl,
		write('Number:'), read(A), nl,
		write('Row: '), read(X), nl,
		write('Column: '), read(Y),
		(
			((A = -2; X = -2; Y = -2), write('Add canceled, exiting...'), B1 is -2);
			addPiece([CorJogador,A],X,Y,B,B1);
			write('Piece not valid'), playerAdd(B,B1,CorJogador)
		).


/*--------------------------------- HUMAN VS PC -------------------------------------------------------------------------------------------------------*/
/* Quando existem adjacentes de menor valor para pc*/
winsBattlePC(0,_,_,_,Board,Board). 
winsBattlePC(N,CorJogador,Row,Column,Board,BF) :- 
		numPieces(CorJogador,Board,Num),
		(
		Num > 1,
			winsBattleAuxPC(CorJogador,Row,Column,Board,BF),
			NF is N - 1,
			winsBattlePC(NF,CorJogador,Row,Column,BF,_);
		write('\nCant change more pieces\n'), 
		BF = Board
		).

winsBattleAuxPC(CorJogador,Row,Column,Board,BF) :- 
		findRandColor(Board,R,C,CorJogador),
		(
		 	(Row \= R; Column \= C),write('PC won a battle and remove piece from row '),write(R), write(' and column '), write(C),nl, changePiece(R,C,Board,BF);
			(winsBattleAuxPC(CorJogador,Row,Column,Board,BF))
		).

/* Calcula as consequencias do movimento duma peca pelo pc*/
calculateConsequencesPC(Board,Row,Column,CorJogador,BF) :- 
		numPieces(CorJogador,Board,Num),
		Num > 1,
		adjacentes(Row,Column,Board,N),
	 	(
	 		N > 0,
	 		winsBattlePC(N,CorJogador,Row,Column,Board,BF);
	 		write('\nNo adjacent pieces with lower value\n'),
			BF = Board
		);
		nl, write('\nCant change pieces yet'), nl,
		BF = Board.

/* Jogar human vs pc */
playerPlayPc(B,Level,CorJogador):- 
		(B = -2, write('\nExiting first...')); /* Jogador decidiu sair do jogo */
		nl, endOfGame(B);
		nl, printboard(B), nl, nl,
		printPlayer(CorJogador), nl,
		(
			(CorJogador = b,				/*human*/
				(
					(existsPiecesInBoard(B,CorJogador),
						write('\nDo you wish to move a piece? (1 for yes, other for no)'), nl,
						read(X),
						(	X = -2, 
								write('\nExiting second...'), B2 is -2;
							X = 1, 
								playerMove(B,B1,CorJogador),
								(
									(B1 = -2, write('\nExiting after move...'));
		 							playerAdd(B1,B2,CorJogador)
								);
							playerAdd(B,B2,CorJogador)
						)
					);

				write('\nCant move pieces yet'),
				playerAdd(B,B2,CorJogador)
				)
			);

			(CorJogador = w,					/*PC*/
				(
					(existsPiecesInBoard(B,CorJogador),
						(
							Level = 1, pcAdd(B,B2,CorJogador)
						);
						(
							Level = 2,
							(random(0,100,R), (R < 50, write('Vai tentar mover'), pcMove(B,B1,CorJogador),pcAdd(B1,B2,CorJogador));
							pcAdd(B,B2,CorJogador))
						);
						(
							Level = 3,
								pcMove(B,B1,CorJogador),
								pcAdd(B1,B2,CorJogador);
							pcAdd(B,B2,CorJogador)
						)


					);

					write('\nPc cant move pieces yet'),
					pcAdd(B,B2,CorJogador)
				)
			)
		),
		(CorJogador = b, playerPlayPc(B2,Level,w); CorJogador = w, playerPlayPc(B2,Level,b)).

/* Mover uma peca */
pcMove(B,BF,CorJogador) :- 
		decideMove(B,CorJogador,BF). 

pcAdd(B,B1,CorJogador) :- 
		findRandEmpty(B,R,C),
		random(0,50,A),
		write('Pc added piece number '), write(A), write(' in row '), write(R), write(' and column '), write(C), nl,nl, 
		(
			addPiece([CorJogador,A],R,C,B,B1);
			pcAdd(B,B1,CorJogador)
		).

/*------------------------------ PC vs PC ----------------------------------------------------------------------------------------------------------*/
pcPlayPc(B,Level,CorJogador):- 
		nl,endOfGame(B);
		sleep(2),				/* Sleep para ser possivel visualizar a jogada do pc */
		nl,printboard(B), nl, nl,
		printPlayer(CorJogador), nl,
		(
			(existsPiecesInBoard(B,CorJogador),
					(
						Level = 1, pcAdd(B,B2,CorJogador)
					);
					(
						Level = 2,
						(random(0,100,R), (R < 50, write('\nVai tentar mover...\n'), pcMove(B,B1,CorJogador),pcAdd(B1,B2,CorJogador));
						pcAdd(B,B2,CorJogador))
					);
					(
						Level = 3,
							pcMove(B,B1,CorJogador),
							pcAdd(B1,B2,CorJogador);
						pcAdd(B,B2,CorJogador)
					)
			);

			write('\nPc cant move pieces yet'),
			pcAdd(B,B2,CorJogador)
		),
		(CorJogador = b, pcPlayPc(B2,Level,w); CorJogador = w, pcPlayPc(B2,Level,b)).

/*----------------------------------------------------------------------------------------------------------------------------------------*/

/* MENU */
play:-
    	cleanScreen,
        write('*******************************************************'), nl,
        write('*******************************************************'), nl,
        write('***                                                 ***'), nl,
        write('***             Welcome to Myriades!                ***'), nl,
        write('***                                                 ***'), nl,
        write('***           1 - Play with default board           ***'), nl,
        write('***            2 - Play with custom board           ***'), nl,
        write('***               3 - Play vs computer              ***'), nl,
        write('***      4 - Play vs computer with custom board     ***'), nl,
        write('***            5 - Computer vs Computer             ***'), nl,
        write('***    6 - Computer vs Computer with custom board   ***'), nl,
        write('***                   7 - About                     ***'), nl,
        write('***                   8 - Exit                      ***'), nl,
        write('***                                                 ***'), nl,
        write('*******************************************************'), nl,
        write('*******************************************************'), nl,
	write('Choice: '), read(X),
	(X = 1,
		initBoard(B,10),
		playerPlay(B,b),
		play;
	X = 2,
		write('Choose board size (2 < size < 11): '),
		read(Size),
		play(Size),
		play;
	X = 3,
		initBoard(B,10),
		level(B,h),
		play;
	X = 4,
		write('Choose board size (2 < size < 11): '),
		read(Size),
		playPc(Size,h),
		play;
	X = 5,
		initBoard(B,10),
		level(B,p),
		play;
	X = 6,
		write('Choose board size (2 < size < 11): '),
		read(Size),
		playPc(Size,p),
		play;
	X = 7,
		about,
		play;
	write('Bye!')
	).


play(N):-
	cleanScreen,
	N > 2, N < 11,
	initBoard(B,N),
	playerPlay(B,b);
	write('Invalid size'),
	pause.

playPc(N,Player):-
	cleanScreen,
	N > 2, N < 11,
	initBoard(B,N),
	level(B,Player);
	write('Invalid size'),
	pause.

about:- cleanScreen,
        write('*******************************************************'), nl,
        write('*******************************************************'), nl,
        write('***                                                 ***'), nl,
        write('***                      ABOUT                      ***'), nl,
        write('***                                                 ***'), nl,
        write('***            To cancel a move, input -1           ***'), nl,
        write('***           To exit at anytime, input -2          ***'), nl,
        write('***                                                 ***'), nl,
        write('***                   Developers:                   ***'), nl,
        write('***                                                 ***'), nl,
        write('***                   Andre Pires                   ***'), nl,
        write('***                   Filipe Gama                   ***'), nl,
        write('***                                                 ***'), nl,
        write('***                                                 ***'), nl,
        write('*******************************************************'), nl,
        write('*******************************************************'), nl,

	pause.

pause:-write('Press any key to continue'), read(_).

level(B,Player):-
	cleanScreen,

	    write('*******************************************************'), nl,
        write('*******************************************************'), nl,
        write('***                                                 ***'), nl,
        write('***                   DIFFICULTY                    ***'), nl,
        write('***                                                 ***'), nl,
        write('***                   1 - Easy                      ***'), nl,
        write('***                   2 - Medium                    ***'), nl,
        write('***                   3 - Hard                      ***'), nl,
        write('***                                                 ***'), nl,
        write('***                                                 ***'), nl,
        write('*******************************************************'), nl,
        write('*******************************************************'), nl,
	write('Choice: '),
	read(D),
	(
		(D=1; D=2; D=3), 
		( Player = h,
			playerPlayPc(B,D,b);
		 Player = p,
		 	pcPlayPc(B,D,b)
		);
		write('Invalid choice\n'),
		level(B,Player)
	).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).

port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	parse_input(ClientMsg, MyReply),
	format(Stream, '~q.~n', [MyReply]),
	write('Wrote: '), write(MyReply), nl,
	flush_output(Stream),
	(ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(comando(Arg1, Arg2), Answer) :-
	comando(Arg1, Arg2, Answer).
	
parse_input(quit, ok-bye) :- !.
		
comando(Arg1, Arg2, Answer) :-
	write(Arg1), nl, write(Arg2), nl,
	initBoard(B,Arg1),
	addPiece([Arg2,3],0,0,B,B1),
	addPiece([Arg2,5],0,1,B1,B2),
	addPiece([Arg2,4],1,1,B2,B3),
	addPiece([Arg2,2],2,3,B3,B4),
	addPiece([Arg2,9],4,2,B4,B5),

	write(B1),
	Answer = B5.
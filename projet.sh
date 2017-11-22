make clean

make all
mkdir perso
clear

echo "----- test affect (prof) -----"
./test_yylex fichier/affect.l > perso/Affect.lex
./test_synt fichier/affect.l > perso/Affect.synt
./test_asynt fichier/affect.l > perso/Affect.asynt
./test_tab fichier/affect.l > perso/Affect.tab
./test_gen fichier/affect.l > perso/Affect.mips
echo "Affect.l => DONE"
echo ""

echo "----- test boucle (prof) -----"
./test_yylex fichier/boucle.l > perso/Boucle.lex
./test_synt fichier/boucle.l > perso/Boucle.synt
./test_asynt fichier/boucle.l > perso/Boucle.asynt
./test_tab fichier/boucle.l > perso/Boucle.tab
./test_gen fichier/boucle.l > perso/Boucle.mips
echo "Boucle.l => DONE"
echo ""

echo "----- test max (prof) -----"
./test_yylex fichier/max.l > perso/Max.lex
./test_synt fichier/max.l > perso/Max.synt
./test_asynt fichier/max.l > perso/Max.asynt
./test_tab fichier/max.l > perso/Max.tab
./test_gen fichier/max.l > perso/Max.mips
echo "Max.l => DONE"
echo ""

echo "----- test tri (prof) -----"
./test_yylex fichier/tri.l > perso/Tri.lex
./test_synt fichier/tri.l > perso/Tri.synt
./test_asynt fichier/tri.l > perso/Tri.asynt
./test_tab fichier/tri.l > perso/Tri.tab
./test_gen fichier/tri.l > perso/Tri.mips
echo "Tri.l => DONE"
echo ""

echo "----- test fibonnachi -----"
./test_yylex fichier/fibonnacci.l > perso/Fibonnacci.lex
./test_synt fichier/fibonnacci.l > perso/Fibonnacci.synt
./test_asynt fichier/fibonnacci.l > perso/Fibonnacci.asynt
./test_tab fichier/fibonnacci.l > perso/Fibonnacci.tab
./test_gen fichier/fibonnacci.l > perso/Fibonnacci.mips
echo "Fibonnaci.l => DONE"
echo ""

echo "----- test collatz -----"
./test_yylex fichier/collatz.l > perso/Collatz.lex
./test_synt fichier/collatz.l > perso/Collatz.synt
./test_asynt fichier/collatz.l > perso/Collatz.asynt
./test_tab fichier/collatz.l > perso/Collatz.tab
./test_gen fichier/collatz.l > perso/Collatz.mips
echo "Collatz.l => DONE"
echo ""

echo "----- test tri sans boucle-----"
./test_yylex fichier/tri_sans_boucle.l > perso/Tri_Sans_Boucle.lex
./test_synt fichier/tri_sans_boucle.l > perso/Tri_Sans_Boucle.synt
./test_asynt fichier/tri_sans_boucle.l > perso/Tri_Sans_Boucle.asynt
./test_tab fichier/tri_sans_boucle.l > perso/Tri_Sans_Boucle.tab
./test_gen fichier/tri_sans_boucle.l > perso/Tri_Sans_Boucle.mips
echo "Tri_Sans_Boucle.l => DONE"
echo ""

echo "----- test factorielle -----"
./test_yylex fichier/factorielle.l > perso/Factorielle.lex
./test_synt fichier/factorielle.l > perso/Factorielle.synt
./test_asynt fichier/factorielle.l > perso/Factorielle.asynt
./test_tab fichier/factorielle.l > perso/Factorielle.tab
./test_gen fichier/factorielle.l > perso/Factorielle.mips
echo "Factorielle.l => DONE"
echo ""

echo "----- test puissance -----"
./test_yylex fichier/puissance.l > perso/Puissance.lex
./test_synt fichier/puissance.l > perso/Puissance.synt
./test_asynt fichier/puissance.l > perso/Puissance.asynt
./test_tab fichier/puissance.l > perso/Puissance.tab
./test_gen fichier/puissance.l > perso/Puissance.mips
echo "Puissance.l => DONE"
echo ""

echo "----- test court-circuit -----"
./test_yylex fichier/court-circuit.l > perso/court-circuit.lex
./test_synt fichier/court-circuit.l > perso/court-circuit.synt
./test_asynt fichier/court-circuit.l > perso/court-circuit.asynt
./test_tab fichier/court-circuit.l > perso/court-circuit.tab
./test_gen fichier/court-circuit.l > perso/court-circuit.mips
echo "court-circuit.l => DONE"
echo ""

echo "----- test associativite -----"
./test_yylex fichier/associativite.l > perso/associativite.lex
./test_synt fichier/associativite.l > perso/associativite.synt
./test_asynt fichier/associativite.l > perso/associativite.asynt
./test_tab fichier/associativite.l > perso/associativite.tab
./test_gen fichier/associativite.l > perso/associativite.mips
echo "associativite.l => DONE"
echo ""

echo "----- test boucle appel -----"
./test_yylex fichier/boucle_appel.l > perso/Boucle_Appel.lex
./test_synt fichier/boucle_appel.l > perso/Boucle_Appel.synt
./test_asynt fichier/boucle_appel.l > perso/Boucle_Appel.asynt
./test_tab fichier/boucle_appel.l > perso/Boucle_Appel.tab
./test_gen fichier/boucle_appel.l > perso/Boucle_Appel.mips
echo "Boucle_Appel.l => DONE"
echo ""




rm *.o

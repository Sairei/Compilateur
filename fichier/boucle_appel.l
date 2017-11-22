entier $n;

boucle(entier $i, entier $a)
{
	$i = $i + 1;

	tantque $i != $a faire
	{
		boucle($i, $a);
	}
	
	$n = $n + $i;
}


main()
entier $a, entier $i;
{
	$a = lire();
	$i = 1;
	$n = 1;

	tantque $i != $a faire
	{
		boucle($i, $a);
	}

	ecrire($n);
}

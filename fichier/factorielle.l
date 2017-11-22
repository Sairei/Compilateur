factorielle(entier $n)
entier $i, entier $a;
{
	$i = 1;
	$a = 1;

	faire
	{
		$a = $a * $i;
		$i = $i + 1;
	}tantque ($i <= $n);

	retour $a;
}

main()
entier $n, entier $a;
{
	$n  = lire();
	$a = factorielle($n);
	ecrire($a);
}

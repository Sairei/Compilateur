puissance(entier $n, entier $p)
entier $i, entier $res;
{
	$i = 1;
	$res = $n;

	si ($p = 0) alors
	{
		retour 1;
	}
	si ($p = 1) alors
	{
		retour $n;
	}
	sinon
	{
		tantque ($i < $p) faire
 		{
			$res = $res * $n;
			$i = $i + 1;
		
		}
		retour $res;
	}
}

main()
entier $n, entier $p, entier $res;
{
	$n = lire();
	$p = lire();
	$res = puissance($n, $p);
	ecrire($res);
}

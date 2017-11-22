entier $nombre;

fibonnacci()
entier $a, entier $b, entier $c, entier $i;
{
	$a = 0;
	$b = 1;
	$i = 1;

	si ($nombre = 0) alors
	{
		retour $a;
	}
	tantque $i < $nombre faire
	{
		$i = $i + 1;		#incrementation possible
		$c = $a + $b;
		$a = $b;
		$b = $c;
	}
	retour $b;
}

main()
entier $n;
{
	$nombre = lire();
	ecrire(fibonnacci());

}

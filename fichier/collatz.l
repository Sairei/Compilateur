collatz( entier $n )
{
	ecrire( $n );
	si( $n = 1 ) alors
	{
		retour 1;
	}
	si( $n%2 = 0 ) alors
	{
		retour collatz($n/2);
	}
	sinon
	{
		retour collatz((3*$n)+1);
	}
}

main()
entier $tmp, entier $n;
{
	$n = lire();
	$tmp = collatz($n);
	ecrire($tmp);
}

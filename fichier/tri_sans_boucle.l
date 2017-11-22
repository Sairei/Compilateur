affiche(entier $n)
{
	ecrire($n);
}

tri(entier $a, entier $b, entier $c)
{
	si ($a < $b) alors
	{
		si ($b < $c) alors
		{
			affiche($a);
			affiche($b);
			affiche($c);
		}
		sinon
		{
			si ($a <= $c) alors
			{
				affiche($a);
				affiche($c);
				affiche($b);
			}
			sinon
			{
				affiche($b);
				affiche($a);
				affiche($c);
			}
		}
	}
	sinon
	{
		si ($c > $a) alors
		{
			affiche($b);
			affiche($a);
			affiche($c);
		}
		sinon
		{
			si ($c >= $b) alors
			{
				affiche($b);
				affiche($c);
				affiche($a);
			}
			sinon
			{
				affiche($a);
				affiche($b);
				affiche($c);
			}
		}
	}
}

main()
entier $a, entier $b, entier $c;
{
	$a = lire();
	$b = lire();
	$c = lire();
	tri($a, $b, $c);
}

main()
entier $a, entier $b;
{
  $a = lire();
  si ($a < 10 & ($a < 10 | $a > 10)) alors
  {
    ecrire(1);

  }
  sinon {
    ecrire(2);
  }

  $b = lire();
  si ($b < 10 | ($b < 5 & $b > 0)) alors
  {
    ecrire(1);
  }
  sinon {
    ecrire(2);
  }

}

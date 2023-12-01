# Závodní trať

Mnoho z Vás nejspíše zaznamenalo úspěchy Ester Ledecké na zimních olympijských hrách v roce 2018, kdy se jí, k úžasu takřka celého nejen sportovního světa, podařilo získat zlatou medaili ve sjezdovém lyžování. BBC dokonce označilo vítězství Ledecké za „jeden z nejúžasnějších olympijských příběhů všech dob.“ Jak již to tak v této naší kotlině bývá, jakmile se našim reprezentantům začne v nějaké disciplíně dařit, hned se celý národ stane nejen naprostým odborníkem, ale také (polo)profesionálním sportovcem. Po Naganu jsme tu tak měli 10 milionů hokejistů, poté se ze všech stali rychlobruslaři (mimochodem, nevíte zda již Martině postavili tu halu?). Později došlo k přeorientaci na biatlon, no a současným králem je právě sjezdové lyžování.

To by v tom byl čert, řekl si jeden Váš známý, říkejme mu pro tuto chvíli Vlekař, aby se z toho nadšení pro lyžování nedala vyždímat nějaká koruna. Netrvalo dlouho, a Vlekař přišel s konkrétním nápadem – uspořádá na své sjezdovce v Osvětamanech Mistrovství České republiky ve sjezdovém lyžování. Proč ta zvedlá obočí? Divíte se, že někdo povolil uspořádat závody ve sjezdu ve skiareálu s nejdelší sjezdovkou dlouho 400 metrů a s převýšením 98 metrů? I když je minimální délka trati pro sjezd podle oficiálních pravidel 800 m? To přeci pro Vlekaře není žádný problém, ten umí i větší věci!

Ale teď vážně. Ve skutečnosti to trochu problém je. Snadno by se mohlo stát, že si některý ze závodníků bude stěžovat a závod bude muset být pro neregulérnost zrušen. No a to by znamenalo nejen zbytečné přípravy, zklamané fanoušky, ale hlavně nutnost vrátit dotaci, kterou Vlekař na závod dostal. A to přeci nechce nikdo, že?

Když jste se o problému dozvěděli, hned Vás napadlo řešení. Areál v Osvětamanech se přeci skládá z několika sjezdovek. Třeba kdyby se podařilo je nějak pospojovat do jedné velké sjezdovky, možná bychom na ten limit dosáhli. Vlekaři se Váš nápad pochopitelně zalíbil a hned Vás poprosil o naplánování nejdelší možné trati.

## Rozhraní programu
Vaším úkolem je implementovat funkci `std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths)`, která v zadané mapě nalezne nejdelší možnou trať pro závod ve sjezdovém lyžování. Trať může začínat a končit na libovolné křižovatce. Parametry jsou počet křižovatek `points` a seznam použitelných cest mezi křižovatkami `all_paths`. Každá cesta obsahuje výchozí křižovatku `from` a cílovou `to` a lze ji projet pouze v tomto směru, protože všechny úseky musí vést z kopce dolů. Také obsahuje délku dané cesty length. Délka je vždy nezáporné celé číslo.

Výstupem je seznam navazujících cest (tj. `to` jedné cesty je `from` té následující), které tvoří nejdelší možnou trať. Pokud je nejdelších tratí více, lze vrátit libovolnou z nich.

Můžete předpokládat, že vstup je vždy platný, tedy:
- Křižovatky, na kterých cesty začínají a končí, jsou z rozsahu `[0, points)`.
- Všechny cesty vedou z kopce dolů.

## Bodové podmínky
- Pro zisk 3 bodů je třeba úlohu korektně vyřešit pro velmi malé instance. Všechny cesty mají délku 10 nebo méně.
- Pro zisk 5 nebo 7 bodů je třeba korektně řešit větší instance, ale délky jednotlivých cest jsou stále omezeny 10.
- Pro zisk 10 bodů je potřeba správně a rychle vyřešit velké instance, které obsahují velmi dlouhé cesty. Stále ale délka přípustné trati nepřesáhne rozsah datového typu `int`.

Časové limity jsou 13 sekund na základní test a 6, 11 a 5 sekund na jednotlivé testy rychlosti. Navíc všechny testy rychlosti dohromady musí doběhnout do 15 sekund.
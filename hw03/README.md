# Vánoční nadílka

Pan Ebenezer Skruž je tvrdá duše! Jak ten umí dřít, lakotit a hromadit majetek! Je ostrý jako křemen, ale nikdy z něj nevykřísne jiskérka šlechetného ohně. Je také uzavřený a spokojený sám se sebou. A samotářský jako ústřice. Chladem, jenž panuje v jeho nitru, mu stará tvář ztuhla, scvrkla se a svraštěla, a jeho špičatý nos se stále víc přiostřuje. Když kráčí po ulici, připomíná ledový rampouch. Oči má zarudlé, rty tenké a zamodralé, a jeho chytrácký hlas zní, jako by skřípalo nenamazané kolo.

Pan Ebenezer Skruž byl, nyní již jediným, partnerem ve společnosti Skruž & Marley. Pan Jakub Marley totiž před sedmi lety zemřel. Skruž, a teď už mrtvý Marley, bývali obchodními společníky celou řadu let. Skruž byl i jediným vykonavatelem jeho poslední vůle, jeho jediným správcem, jediným dědicem, jediným přítelem a snad i jediným truchlícím. Ale ani Skruž nebyl tou smutnou událostí příliš zdrcen, jak lidé očekávali. I v den pohřbu si zachoval chladnou obchodní mysl a oslavil jej dobře uzavřeným obchodem.

Dnes v noci měl pan Skruž velmi neklidné spaní. A přitom k tomu nebyl žádný viditelný důvod: i přes blížící se Štedrý den, kdy většina darmožroutů odmítá pracovat, se mu podařili vyjednat hned několik výtečných obchodů. Že by to způsobili Ti dva budižkničemové, co si dovolili ho dnes vyrušit?

<i>

Asi okolo poledního vstoupili do kanceláře dva muži příjemného zevnějšku, s klobouky a s listinami v rukou, a tvářili se skromně a zdvořile. „Firma Skruž a Marley, že?“ pravil s úklonou jeden z pánů a podíval se do listiny. „Mám to potěšení mluvit s panem Skružem, nebo s panem Marleym?“

„Pan Marley zemřel před sedmi lety,“ odpověděl Skruž.

„Doufám, že jeho štědrost přešla na žijícího společníka,“ řekl jeden z pánů a podával Skružovi svou navštívenku.

Skruž se zamračil a potřásl nevlídně hlavou.

„V této sváteční době, pane Skruži,“ pravil pán a vzal do ruky pero, „je více než kdy jindy žádoucí, abychom se podle možností postarali o chudé a opuštěné. Ti zvlášť nyní nejvíc trpí. Tisíce lidí nemají nejnutnější potřeby a nemají ani teplo, pane.“

</i>

Ještě toho tolik, dávat své těžce vydělané peníze nějakým otrapům, kteří se o sebe neumí sami postarat. Jen s nataženou rukou čekají, kdo jim co dá. Jak si na to pan Skruž vzpomněl, úplně se rozčilením probral. Rozžal petrolejovou lampu, která stála na zemi vedle postele, a vydal se do kuchyně pro sklenici vody.

„Sním, či bdím?“ ptal se sám sebe pan Skruž, když vešel do kuchyně. O trochu zvětšil plamen lampy, aby se přesvědčil, že ho něšálí zrak. No opravdu, u stolu někdo sedí. To je ale nebetyčná drzost! Ale počkat, počkat. To není jen tak někdo. Vždyť ta postava jako by z oka vypadla panu Jakubu Marleymu. „Jsi to ty, Jakube?“ zeptal se nesměle pan Skruž.

„To víš že jsem to já, starý brachu,“ pronesla osoba a začala se zvedat ze svého místa u stolu. „Musel jsem se vrátit, protože jsi porušil mou poslední závěť! V ní bylo jasně uvedeno, že každé Vánoce věnuješ každému ze zaměstnanců našeho obchodu dárek tak, jak jsem to dělal já. Vím, že jsi s tím nikdy nesouhlasil, ale bylo to mé poslední přání. To si říkáš kamarád?“ Při posledních slovech již pan Marley svíral rameno pana Skruže, který stál jako přikovaný a nevěřícně poslouchal. „Dnes v noci Tě navštíví ještě tři další duchové, kteří ti jasně ukáží, co tě čeká, pokud budeš dále lakotit a svůj slib, který jsi mi dal převzetím mého dědictví, nenapravíš,“ dodal pan Marley a náhle zmizel.

Co dál se v noci panu Skružovi přihodilo není nyní podstatné. Důležité je, že druhý den přišel do obchodu a byl jako vyměněný. Představte si, že si do své kanceláře zavolal svého pomocníka Boba, kterému nařídil sehnat vánoční dárky pro zaměstnance.

Je nasnadě, že pan Skruž nedal Bobovi úplně volnou ruku. Připravil mu totiž seznam povolených dárků společně s jejich cenami. A dodal, že Bob musí pořídit dárky co nejlevněji a přitom dodržet následující pravidlo: žádný zaměstnanec nesmí dostat stejný dárek jako jeho nadřízený. A tak Bob nyní sedí sklesle ve své kanceláři a snaží se přijít na to, kterému zaměstnanci koupit který dárek. Dokážeš mu s výběrem pomoci?


## Rozhraní programu
Vaším úkolem je implementovat funkci `optimize_gifts`, která každému zaměstnanci přiřadí vánoční dárek. Žádný zaměstnanec nesmí dostat stejný dárek jako jeho přímý nadřízený nebo některý z jeho přímých podřízených. Zároveň chcete minimalizovat celkovou cenu dárků. Argumenty funkce jsou:

`std::vector<Employee> boss`: Zaměstnanci jsou pro ochranu osobních údajů označeni čísly od 0 do jejich počtu mínus jedna. Toto pole tak svou velikostí udává počet zaměstnanců a na i-té pozici je uvedené číslo přímého nadřízeného zaměstnance i. Pokud zaměstnanec nemá nadřízeného, je tam uvedena konstanta `NO_EMPLOYEE`. Žádný zaměstnanec není ani nepřímo vlastním nadřízeným.

`std::vector<Price> gift_price`: Seznam cen dárků schválených panem Skružem.

Návratová hodnota je dvojice `std::pair<Price, std::vector<Gift>>`, kde druhá položka je seznam, který na pozici i obsahuje číslo dárku (dle pole `gift_price`s) přiřazeného zaměstnanci i, a první položka je součet cen všech přiřazených dárků. Můžete předpokládat, že vstup je korektní.

## Bodové podmínky
Pro zisk 3 bodů je třeba korektně vyřešit malé instance řádově o desítkách zaměstnanců a jednotkách dárků. (Časový limit je 15 sekund.)
Pro zisk 6 až 10 bodů je třeba již naivní implementace nepostačuje. (Časové limity jsou 1, 1 a 6 sekund.)
Bonus: Pro zisk až 11.5 bodu je třeba řešení nejen rychlé asymptoticky, ale i efektivně naprogramované. Pro zisk bodů z bonusu je časový limit 4.5 sekundy, pro plný počet bodů je limit 2.5 sekundy.
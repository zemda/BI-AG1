# Textový editor


Před dávnými časy, v předaleké galaxii, žily na planetě Zemi dva naprosto nesmiřitelné kmeny uživatelů. Každý z kmenů uctíval jako svého boha jeden ze dvou velice mocných textových editorů: Vim a Emacs. Jednou z nejdůležitějších životních náplní (a zlí jazykové tvrdí, že pro některé to byla náplň jediná) těchto uživatelů bylo vést vášnivé internetové diskuze o tom, který z editorů je lepší. Každý z nich tvrdil, že jeho editor je ten nejlepší a že ten druhý by měl být pro nízkou efektivitu zakázán příslušnými úřady.

Avšak v jednom malém koutě této planety se narodil mladý a nadějný programátor jménem Elon, jehož myšlenky byly jiné než ostatních. Vnímal nesmiřitelný boj mezi Vimem a Emacsem jako ztrátu času a energie. Byl přesvědčen, že by bylo mnohem lepší, kdyby se spojily nejlepší vlastnosti obou editorů do jednoho všestranného nástroje.

Tak Elon začal pracovat na projektu, který měl přinést jednotu mezi uživatel Vimu a Emacsu. Rozhodl se tedy vytvořit úžasný textový editor, který bude kombinovat sílu Vimových zkratek s flexibilitou Emacsových rozšíření. Ale to nebylo vše. Elon chtěl, aby jeho editor byl tak revoluční, že by nadchl nejen pokročilé uživatele textových editorů, ale celou planetu, včetně tzv. BFU. Proto se rozhodl, že spojí ještě dvě důležité vlastnosti každého z editorů: z prostředí Emacsu zakomponuje poučku „dobrý operační systém, ale špatný editor“, z Vimu pak do nového editoru přenese nemožnost editor vypnout.

Elon, který si liboval v efektivitě, se rozhodl svůj editor pojmenovat χ. Právě χ se měl stát symbolem spojení, pokroku, svobody a míru na celé Zemi. A od té doby žili programátoři v harmonii, každý mohl používat χ podle svého gusta a nikdo už se nezabýval hádkami mezi Vimem a Emacsem. Byli šťastní a tvořili spolu úžasné programy a projekty, protože χ jim umožňoval dosáhnout maxima jejich tvůrčí síly.



Opravdu věříš, že by se něco takové mohlo stát? Kdepak, to je jenom pohádka. Elon ve skutečnosti sám moc programovat neumí, je dobrý spíše v impulzivním rozhodování, krizovém managementu a marketingu. Požádal tě proto, zda bys mu s programováním editoru nepomohl. Výměnou za tvých 120 hodin práce týdně ti slibuje, že až χ vypustí do světa, budeš uveden v seznamu autorů hned na druhém místě.

## Rozhraní programu
Vaším úkolem je implementovat třídu `TextEditorBackend`, která představuje backend textového editoru. Požadované rozhraní:
```c
TextEditorBackend(const std::string& text): konstruktor, který inicializuje obsah editoru daným textem.

size_t size() const: Počet znaků textu včetně nových řádků.

size_t lines() const: Počet řádků. Prázdný text má jeden řádek. Každý znak \n přidá řádek.

char at(size_t i) const: Vrátí i-tý znak. Povolený rozsah je [0, size()).

void edit(size_t i, char c): Nahradí znak na pozici i znakem c. Povolený rozsah je [0, size()).

void insert(size_t i, char c): Vloží znak c před znak na pozici i. Povolený rozsah je [0, size()].

void erase(size_t i): Smaže znak na pozici i. Povolený rozsah je [0, size()).

size_t line_start(size_t r) const: Vrátí začátek r-tého řádku. Znak \n je součástí řádku, který ukončuje. Povolený rozsah je [0, lines()).

size_t line_length(size_t r) const: Vrátí délku i-tého řádku včetně případného znaku \n na konci. Povolený rozsah je [0, lines()).

size_t char_to_line(size_t i) const: Vrátí číslo řádku, na kterém se nachází i-tý znak. Povolený rozsah je [0, size()).

```
Pokud je metoda volána s argumentem mimo rozsah, musí vyvolat výjimku `std::out_of_range`. Metody `size` a `lines` by měly mít konstantní složitost. Ostatní metody by měly mít logaritmickou složitost. Konstruktor by neměl být pomalejší, než opakované volání metody `insert`.

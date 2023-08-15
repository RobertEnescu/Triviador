#include "TriviadorDatabase.h"

TriviadorDatabase::TriviadorDatabase(Storage& storage)
	:m_db{ storage }
{
}

void populateStorageQuestions(Storage& storage)
{
	using namespace dbClasses;
	std::vector<Question> questions = {
	Question{-1,"De cate ori au fost Patriots in jocul final al Super Bowl?", 11 },
	Question{-1,"Care este temperatura medie (in grade C ) a suprafetei pe Venus?", 460 },
	Question{-1,"In ce an Beatles a plecat prima data in SUA?", 1964 },
	Question{-1,"In ce an s-a mutat Arsenal pe stadionul Emirates din Highbury?", 2006 },
	Question{-1,"In ce an a fost lansat pentru prima data The Godfather?", 1972 },
	Question{-1,"Cate goluri din Liga a marcat Jurgen Klinsmann pentru Tottenham Hotspur in sezonul Premier League 1994/1995?", 21},
	Question{-1,"In ce an a fost produsul WD40 inventat de chimistul Norm Larsen?",1953 },
	Question{-1,"In ce an s-a nascut Regele Mihai I?",1921 },
	Question{-1,"Cate strofe are poezia `Luceafarul` de Mihai Eminescu ? ",98 },
	Question{-1,"Cate minute are pauza unui meci de fotbal?",15 },
	Question{-1,"Cate zile are un an bisect?",366 },
	Question{-1,"Cati ani a durat Razboiul de 100 de ani?",116 },
	Question{-1,"In ce an a intrat Romania in Uniunea Europeana?",2007 },
	Question{-1,"In ce an a murit Printesa Diana?",1997 },
	Question{-1,"In ce an a primit Michael o stea pe bulevardul Hollywood?",1984 },
	Question{-1,"In ce an s-a sfarsit primului razboi mondial?",1918 },
	Question{-1,"Cate calorii are un mar/100 de grame?",52 },
	Question{-1,"Cate tari se invecineaza cu Romania?",5 },
	Question{-1,"Cate state folosesc unitati monetare numite `leu?`",2 },
	Question{-1,"O data la cati ani are loc Campionatul Mondial de fotbal?",4},
	Question{-1,"Cata campionate mondiale are Brazilia in palmares?",5 },
	Question{-1,"In ce an a fost creata Organizatia Natiunilor Unite (ONU)?",1945 },
	Question{-1,"In ce an a fost asasinat John F. Kennedy?",1963 },
	Question{-1,"Cu ce viteza calatoreste lumina in km/s?",300000 },
	Question{-1,"Cate elemente are tabelul periodic?",118 },
	Question{-1,"Cate continente exista pe Pamant?",7 },
	Question{-1,"Cate zile are luna decembrie?",31 },
	Question{-1,"Cate planete exista in sistemul solar?",8 },
	Question{-1,"Cate litere are alfabetul englez?",26 },
	Question{-1,"Cate zile are o saptamana?",7 },
	Question{-1,"Cate minute are o ora?",60 },
	Question{-1,"Cate secunde are o ora?",3600 },
	Question{-1,"Cati ani are un secol?",100 },
	Question{-1,"In ce an s-a proclamat independenta de stat a Romaniei?",1877 },
	Question{-1,"Cat inseamna o duzina?",12},
	Question{-1,"Cate picioare are un centiped?",100},
	Question{-1,"A cata misiune Apollo a fost cea care  a dus cu succes 2 oameni pe luna?",11},
	Question{-1,"Cati jucatori sunt intr-o echipa de basket?",5},
	Question{-1,"Cate grade a avut cel mai puternic cutremur din lume? (aproximat)?",9},
	Question{-1,"In ce an s-a presupus ca s-a termiant calendarul maias?",2012},
	Question{-1,"Cate zile are un an bisect?",366},
	Question{-1, "In ce an a avut loc batalia de la Vaslui?",1475},
	Question{-1,"Cati ani a trait cel mai batran om din lume?",116},
	Question{-1, "Cate molecule de oxigen se regasec in acidul sulfuric",4},
	Question{-1,"In ce an a avut loc atentatul de la turnurile gemene?",2001},
	Question{-1,"In ce an a avut loc atentatul de la Hiroshima",1945},
	Question{-1,"Care este durata medie de viață a unui om?",80},
	Question{-1,"Câți kilometri este distanța dintre New York și Londra?(KM)",5500},
	Question{-1,"Câți ani are Pământul?(miliarde de ani)",5},
	Question{-1,"Câți centimetri sunt într-un metru?",100},
	Question{-1,"Câți ani a durat Războiul de o sută de ani?",116},
	Question{-1,"Câte mile este distanța în jurul ecuatorului Pământului?(mile)",24901},
	Question{-1,"Câți ani a durat Republica Romană?",482},
	Question{-1,"Câți galoane de apă folosește o persoană în medie pe zi?",90},
	Question{-1,"Câți ani a durat Războiul Rece?",44},
	Question{-1,"Câți kilometri pătrați este suprafața Franței?(kilometri pătrați)",643879}

	};
	storage.insert_range(questions.begin(), questions.end());
}

void populateStorageQuestionsMultipleChoice(Storage& storage)
{
	using namespace dbClasses;
	std::vector<QuestionMultipleChoice> questionsMultipleChoice = {
	QuestionMultipleChoice{-1,"Cui ii apartine melodia What Do You Want From Me? (albumul The Division Bell 1994)?","Pink Floyd","Syd Barret","Pink Floyd","David Gilmour","Nick Mason"},
	QuestionMultipleChoice{-1,"Ce echipa a castigat Campionatul Mondial de fotbal din 2002?","Brazilia","Romania","Franta","Brazilia","SUA"},
	QuestionMultipleChoice{-1,"Care este primul element din tabelul periodic?","Hidrogen","Hidrogen","Argint","Aur","Oxigen"},
	QuestionMultipleChoice{-1,"Ce inseamna simbolul K in tabelul periodic?","Potasiu","Hidrogen","Potasiu","Curium","Krypton"},
	QuestionMultipleChoice{-1,"Pe ce melodie intra de obicei Ian la concerte?","Michael Jackson","Veste","Slayer 2","Michael Jackson","Kika"},
	QuestionMultipleChoice{-1,"Care este cel mai mare animal de pe planeta?","Balena albastra","Megalodon","Elefantul","Orca","Balena albastra"},
	QuestionMultipleChoice{-1,"Care este capitala Spaniei?","Madrid","Barcelona","Maroc","Madrid","Valencia"},
	QuestionMultipleChoice{-1,"Care este capitala Frantei?","Paris","Lyon","Anglia","Bucuresti","Paris"},
	QuestionMultipleChoice{-1,"Cate elemente are tabelul periodic?","18","16","10","30","18"},
	QuestionMultipleChoice{-1,"Care este cel mai mare organ intern al corpului uman?","Ficatul","Plamanul","Inima","Ficatul","Rinichiul"},
	QuestionMultipleChoice{-1,"In ce an a fost asasinat John F. Kennedy?","1963","1980","1963","2005","1956"},
	QuestionMultipleChoice{-1,"Ce organism al U.E. isi are sediul la Strasbourg?","Consiliul Europei","Consiliul Europei","ONU","Comisia Europeana","Parlamentul European"},
	QuestionMultipleChoice{-1,"Ce companie a creat jocul League of Legends?","Riot Games","Valve","Riot Games","Electronic Arts","Activision"},
	QuestionMultipleChoice{-1,"Ce companie a creat jocul Counter Strike:Global Offensive?","Valve","Valve","Riot Games","Electronic Arts","Activision"},
	QuestionMultipleChoice{-1,"Ce poet avea profesia de medic?","Vasile Voiculescu","Mihai Eminescu","Vasile Voiculescu","Marin Sorescu","Liviu Rebreanu"},
	QuestionMultipleChoice{-1,"In ce oras a murit Nichita Stanescu?","Bucuresti","Viena","Fagaras","Brasov","Bucuresti"},
	QuestionMultipleChoice{-1,"Unde s-a nascut Ion Creanga?","Humulesti","Vaslui","Botosani","Humulesti","Bucuresti"},
	QuestionMultipleChoice{-1,"In ce an a fost descoperit radonul?", "1900", "1911","1900","1936", "1922"},
	QuestionMultipleChoice{-1,"In ce tara a avut loc Campionatul Mondial de fotbal din 2010?", "Africa de Sud", "Brazilia", "Germania", "Italia", "Africa de Sud"},
	QuestionMultipleChoice{-1,"Cine a castigat Campionatul Mondial de fotbal din 2014?","Germania","Germania","Argentina","Brazilia","Spania"},
	QuestionMultipleChoice{-1,"In ce tara a avut loc Campionatul Mondial de fotbal din 1998?","Franta","Brazilia","Italia","Franta","Spania"},
	QuestionMultipleChoice{-1,"Cine a castigat Campionatul Mondial de fotbal din 2006?","Italia", "Argentina", "Brazilia",  "Spania", "Italia"},
	QuestionMultipleChoice{-1,"Cine a fost presedintele Romaniei intre anii 2004-2014?", "Traian Basescu", "Traian Basescu", "Nicolae C. Paulescu", "Klaus Iohannis", "Carol I"},
	QuestionMultipleChoice{-1,"In ce tara a avut loc Campionatul Mondial de fotbal din 2002?","Coreea de Sud si Japonia","Brazilia","Germania","SUA","Coreea de Sud si Japonia"},
	QuestionMultipleChoice{-1,"Cine este vocalistul Five Finger Death Punct?","Freddy Mercury","Stefan Banica","Cargo","Ivan Moody","Ivan Moody"},
	QuestionMultipleChoice{-1,"Cine a infiintat trupa CTC?","Deliric","VD","VF","DOC","Deliric"},
	QuestionMultipleChoice{-1,"Care dj s-a alaturat trupei BUG Mafia in anul 2004?","DJ Nasa","DJ Paul", "FreakaDaDisk","PRNY","DJ Paul"},
	QuestionMultipleChoice{-1,"Care dintre urmatoarele firme de autocamioane este romaneasca?","M.A.N","Volvo","DAF","Renault","M.A.N"},
	QuestionMultipleChoice{-1,"In ce judet s-a nascut Andra Maruta?","Iasi","Vaslui","Campia Turzii","Valcea","Campia Turzii"},
	QuestionMultipleChoice{-1,"In ce mitologie apare zeita Afrodita?","egipteana","romana","maiasa","greaca","greaca"},
	QuestionMultipleChoice{-1,"Care este viteza im km/h a celei mai rapide masini de formula 1?","223","372","198","425","372"},
	QuestionMultipleChoice{-1,"Cine a compus Waltz No.2?","Ludwig van Beethoven","Da Vinci","Leonardo Di Caprio", "Dimitri Shostakovich", "Dimitri Shostakovich"},
	QuestionMultipleChoice{-1,"Cate strofe are luceafarul de Mihai Eminescu?","100","98","102","97","98"},
	QuestionMultipleChoice{-1,"Ce rasa de caine este cunoscutul Scooby Doo?","Ciobanesc","Golden Retriever","Marele Danez","Pechinez","Marele Danez"},
	QuestionMultipleChoice{-1,"Care este cel mai frecvent nume romanesc?","Andrei","Daniel","George","Raul","Andrei"},
	QuestionMultipleChoice{-1,"Cum este cunoscuta a doua parte a Bibliei?","Vechiul Testament","Prima parte","A doua parte","Noul Testament","Noul Testament"},
	QuestionMultipleChoice{-1,"Cu ce arma l-a invins David pe Goliat?","Sabie","Arch","Buzdugan","Prastie","Prastie"},
	QuestionMultipleChoice{-1,"Ce masina a fost prima care a avut autopilot?","WolksWagen","Audi","Mercedes","Tesa","Tesla"},
	QuestionMultipleChoice{-1,"Cine a fondat Principatul Țării Românești?","Vlad Dracula","Mircea cel Bătrân","Ștefan cel Mare","Mihai Viteazul","Mircea cel Bătrân"},
	QuestionMultipleChoice{-1,"Care a fost motivul principal pentru ocupația otomană a României?"," Motive economice","Motive politice","Motive religioase","Motive militare","Motive militare"},
	QuestionMultipleChoice{-1,"Cine a fost liderul României în timpul celui de-al Doilea Război Mondial?","Ion Antonescu","Nicolae Ceaușescu","Ion Iliescu","Traian Băsescu","Ion Antonescu"},
	QuestionMultipleChoice{-1,"Când a devenit oficial România o țară comunistă?","1944","1948","1952","1956","1948"},
	QuestionMultipleChoice{-1,"Cine a fost primul președinte ales democratic al României?","Ion Antonescu"," Nicolae Ceaușescu","Ion Iliescu","Emil Constantinescu","Emil Constantinescu"},
	QuestionMultipleChoice{-1,"În ce an România a aderat la Uniunea Europeană?","1995","2004","2007"," 2013","2004"},
	QuestionMultipleChoice{-1,"Care este cel mai mare organism viu de pe Pământ?","Balenă albastră","Copac din lemn rosu","Calamar gigant","Girafele","Copac din lemn rosu"},
	QuestionMultipleChoice{-1,"Care este procesul prin care plantele își fac propria hrană?","Fotosinteză","Digestie","Respiraţie","Metabolism","Fotosinteză"},
	QuestionMultipleChoice{-1,"Care este sursa primară de energie pentru toate organismele vii?","Lumina soarelui","Apa","Oxigen","Dioxid de carbon","Lumina soarelui"},
	QuestionMultipleChoice{-1,"Care este cel mai frecvent tip de precipitații?","Ploaie","Zăpadă","Lapoviță","Grindină","Ploaie"},
	QuestionMultipleChoice{-1,"Care este principalul gaz care alcătuiește atmosfera Pământului?","Azot","Oxigen","Dioxid de carbon","Metan","Azot"},
	QuestionMultipleChoice{-1,"Care este termenul pentru schimbarea treptată a caracteristicilor unei specii în timp?","Evoluţie","Adaptare","Migrația","Extincţie","Evoluţie"},
	QuestionMultipleChoice{-1,"Cum se numește procesul prin care vaporii de apă din aer se transformă în lichid?","Condensare","Evaporare","Sublimarea","Congelare","Condensare"}



	};
	storage.insert_range(questionsMultipleChoice.begin(), questionsMultipleChoice.end());
}

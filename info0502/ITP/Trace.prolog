%Importation tres 'propre' de divinites
divinite_primordiale(chaos).
divinite_primordiale(nyx).
divinite_primordiale(erebe).
divinite_primordiale(tartare).
divinite_primordiale(eros).
divinite_primordiale(gaia).
divinite_primordiale(ouranos).

titan(cronos).
titan(rhea).

divinite(zeus).
divinite(hestia).
divinite(poseidon).
divinite(hera).
divinite(ares).
divinite(hephaistos).
divinite(apollon).
divinite(artemis).
divinite(dionysos).
divinite(athena).
divinite(hermes).

divinite(eris).
divinite(demeter).
divinite(hades).
divinite(persephone).
divinite(ilithye).
divinite(hebe).
divinite(leto).
divinite(semele).
divinite(metis).
divinite(maia).

demi_divinite(heracles).

male(zeus).
male(chaos).
male(erebe).
male(tartare).
male(eros).
male(ouranos).
male(chronos).
male(poseidon).
male(hades).
male(ares).
male(hephaistos).
male(heracles).
male(apollon).
male(dionysos).
male(hermes).

femelle(nyx).
femelle(gaia).
femelle(eris).
femelle(rhea).
femelle(aphrodite).
femelle(hestia).
femelle(demeter).
femelle(hera).
femelle(persephone).
femelle(ilithye).
femelle(hebe).
femelle(alcmene).
femelle(leto).
femelle(semele).
femelle(metis).
femelle(maia).
femelle(artemis).
femelle(athena).

divinite_male(X):-divinite(X),male(X).

testdivinite_male(X):-trace,divinite_male(X),notrace,nodebug.
%Pour dionysos, divinite_male(X) fait apparaitre 3 Call, 3 Exit, 0 Redo

The Illinois Speech and Language Engineering Dictionary (isledict)
Version 0.2

ISLEdict is designed to have the following features:

 1. Redistributable.  All sources for this dictionary allow
    redistribution (see SOURCES.bib for a list of sources).  All
    entries in this dictionary may be edited and redistributed,
    subject to only one condition: If your redistributed version
    includes the Edinburgh unigram language model log probabilities
    (fields of the form "(nnp -11.403)") then when you redistribute,
    you must include the file COPYING.poslex in your distribution.

 2. Reliable.  90% of the pronunciations and lexical stress markings
    in isledict come from the Carnegie Mellon Pronouncing Dictionary
    (v0.6, 1998).  CMUdict has been a standard reference for nine
    years, so we consider it a reliable baseline to start from.  About
    4k of the 137k entries in ISLEdict have been checked by hand for
    errors of pronunciation, syllabification, part of speech, or named
    entity tags, and a few systematic errors were identified and
    corrected.  If you find errors that we missed, please tell me:
    jhasegaw@uiuc.edu.

    Notes on reliability:

    - Words with pronunciation but no part of speech tags are words
      that have not been verified or could not be verified.  Most of
      these words will eventually be verified, but some may be
      unverifiable, either because they are neologisms from some
      corpus or other, or because they are mistakes.  They remain in
      the dictionary for now, in case you find them useful.

    - Words marked "(fw misspelling)" are words known to be
      misspelled, usually from the Switchboard dictionary.  They
      remain in the dictionary because they may be useful in
      Switchboard training.

 3. Useful out-of-the-box.  This dictionary includes every entry in
    the Mississippi State Switchboard dictionary, including fragments,
    digit strings, neologisms, mispronunciations, and misspellings.
    Therefore you should be able to train a Switchboard recognizer
    using this dictionary without any special manipulation of
    fragments, digit strings, etc., etc.

 4. Feature-rich.  The dictionary includes the following information.
    Phonemic pronunciation, syllabification, and lexical stress are
    available for every word in the dictionary, because we have only
    listed words for which those features exist.  Part of speech and
    named entity tags (when appropriate) exist for most words.
    Morphology exists for only a few words.

    a. Phonemic pronunciation and lexical stress are derived primarily
    from the CMU pronouncing dictionary, version 0.6, augmented by
    rules applied to the Switchboard dictionary.  Format is the same
    as the CMU dictionary: see README-PHONES.txt.

    b. Syllabification was derived by rule at the University of
    Illinois.

    d. Part of speech is derived from the Edinburgh WSJ corpus, from
    the SIL KTagger program, and from named entity files: see
    README-POS.txt.

    e. Named entity tags are labeled with "nnp" or "nnps", followed by
    the named entity type.  The following tags currently exist.

       - (nnp (surname|boyname|girlname) \d\.\d\d\d) specifies that
         the entry was logged as a surname, male given name, or female
         given name in the 1990 U.S. Census, or was listed as one of
         these name types in a relevant wikipedia entry.  The number
         at the end of the entry specifies the percent frequency of
         the surname, male name, or female name in 1990 U.S. Census
         data, rounded to the nearest thousandth of one percent.

       - (nnp person) is usually a professional title.

       - (nnp city) tags include cities with more than 100,000
         inhabitants, U.S. state capitols, and other cities.
	
       - (nnp country) includes many member states of the United
         Nations, and an assortment of other country-like entities
         (dependent protectorates, historical nations, etc.).  (nnp
         continent) and (nnp state) are used to mark continents and
         U.S. states.

       - (nnp place) is used for other places including rivers,
         mountains, planets and moons, and mythical places.

       - (nnp product) is used generically for registered trademarks,
         generic names of medicines, types of music, and names of
         philosophies (e.g., dixieland (nnp product)).

       - (nnp company) is a for-profit corporation; (nnp organization)
         is any non-country, non-company organization.

       - (nnp event) is an event, date, or period of time, e.g.,
         Christmas.  Adjectives such as "jurassic" and "medieval" are
         marked as jj, not nnp.

    f. Morphology: two types of morphological information are provided
    by the SIL KTagger program for the words it knows (with some extra
    labels provided by hand):

      - (<pos> root:<root>) specifies the root word

      - (morphology:...+...) specifies orthographic morpheme
        decomposition for words with known non-trivial decomposition


Mark Hasegawa-Johnson
jhasegaw@uiuc.edu
June 6, 2007

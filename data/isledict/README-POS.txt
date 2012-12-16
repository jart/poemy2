README: PARTS OF SPEECH

I. SOURCES

Part-of-speech annotations in the ISLE-June-2007 dictionary come from
three sources: (1) wsj.wp39.poslexR, part of the Festival distribution
(see COPYING.poslex), apparently created by using an automatic POS
tagger on the words of the CMU-0.4 pronouncing dictionary, (2)
cmudict-0.4.out, also part of the Festival distribution, which
includes a few pronunciation variants apparently manually marked for
part of speech, and (3) c06d_ktagged and sw-ms98-ktagged.txt, files
which were created by applying SIL's KTagger program to the files c06d
and sw-ms98-dict.txt, respectively.  These sources have been merged
and checked at Illinois.

II. TAG CATEGORIES

Two types of POS tag are used in the dictionary:

(1) Treebank POS tags are listed in parentheses after the word when
    available (usually only available if the word was in
    wsj.wp39.poslexR).  If more than one POS tag apply to a given
    word/superclass entry, then all matching tags are listed in order,
    together with their WSJ unigram log probabilities if available.

(2) Pronunciation variants are distinguished only on the basis of POS
    superclass.  The superclass for each Treebank tag is listed
    below. This choice has had only one negative consequence so far:
    it eliminates the difference between lead (VP, /liyd/) and lead
    (VBN, /lehd/).  That difference seems to be an artifact, therefore
    the latter pronunciation has been eliminated from the dictionary
    (in favor of the unambiguous spelling "led").

III. TREEBANK SUPERCLASS LEXICON

c. Conjunction

Coordinating conjunction|CC 

d. Determiner

Article/Determiner|DT
Predeterminer|PDT 

e. Existential

Existential "there"|EX

f. Foreign Word

Foreignword|FW

i. Preposition or Particle

Preposition or subordinating conjunction|IN 
Particle|RP

j. Adjective

Adjective|JJ 
Adjective,comparative|JJR 
Adjective,superlative|JJS 
Ordinal number|JJ
Possessive ending|POS

Note: In treebank, the word "John's" would be two tokens: "John/NNP
's/POS".  The closest approximation to this notation that we can
implement in ISLEdict is to give "John's" both parts of speech:
"john's(j,n)(nnp boyname 3.271)(pos root:john)".

n. Noun

Noun, plural|NNS 
Noun, singular or mass|NN
Proper noun, plural|NNPS
Proper noun, singular|NNP
Cardinal number|CD

o. Of

Of|OF

p. Pronoun

Personal or possessive pronoun|PRP

r. Adverb

Adverb or Negation|RB 
Adverb,comparative|RBR 
Adverb,superlative|RBS

s. Punctuation/Symbol

List item marker|LS
Punctuation|PUNC
Symbol|SYM

t. To

to|TO

u. Exclamation/Interjection

Exclamation or Interjection|UH

v. Verb

Verb, baseform|VB
Verb, past tense|VBD
Verb, gerund or present participle|VBG 
Verb, past participle|VBN
Verb, present tense, other than 3rd person singular|VBP 
Verb, present tense, 3rd person singular|VBZ
Verb, modal|MD

w. Wh-words

Wh-determiner|WDT 
Wh-pronoun|WP
Wh-pronoun,possessive|WP$
Wh-adverb|WRB


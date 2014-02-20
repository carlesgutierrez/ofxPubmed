//
//  ofxPubMed.h
//  httpRequestPubMed
//
//  Created by Carles on 19/02/14.
//
//

#ifndef __httpRequestPubMed__ofxPubMed__
#define __httpRequestPubMed__ofxPubMed__

#include <iostream>
#include "ofMain.h"
#include "ofxJSONElement.h"

#define MAXITEMS 41

class ofxPubMed {
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    
    void applyRequest();
    
    
    void starteSearchRequest(string item, string addtype);
    void addANDSimpleTagRequest(string newitem, string addtype);
    void addORSimpleTagRequest(string newitem, string addtype);
    void addConsecutiveTagRequest(string newitem, string addtype);
    
    


private:

    string myVisibleSelItems[MAXITEMS] = {"[Alliation]","[All Fields]", "[Author]", "[Author-Corporate]", "[Author-First]", "[Author - Full]", "[Author - Identifier]", "[Author - Last]", "[Book]", "[Date - Completion]", "[Date - Create]", "[Date - Entrez]","[Date - MeSH]", "[Date - Modification]", "[Date - Publication]", "[EC/RN Number]", "[Editor]", "[Filter]", "[Grant Number]", "[ISBN]", "[Investigator]", "[Investigator - Full]", "[Issue]", "[Journal]", "[Language]", "[Location ID]", "[MeSH Major Topic]", "[MeSH Subheading]", "[MeSH Subheading]", "[Other Term]", "[Pagination]", "[Pharmacological Action]", "[Publication Type]", "[Publisher]", "[Secondary Source ID]", "[Supplementary Concept]", "[Text Word]", "[Title]", "[Title/Abstract]", "[Transliterated Title]", "[Volume]"};


    string myRequestSelItems[MAXITEMS] = {"[Alliation]","[All%20Fields]", "[Author]", "[Author%20-%20Corporate]", "[Author%20-%20First]", "[Author%20-%20Full]", "[Author%20- Identifier]", "[Author%20-%20Last]", "[Book]", "[Date%20-%20Completion]", "[Date%20-%20Create]", "[Date%20-%20Entrez]","[Date%20-%20MeSH]", "[Date%20-%20Modification]", "[Date%20-%20Publication]", "[EC/RN%20Number]", "[Editor]", "[Filter]", "[Grant%20Number]", "[ISBN]", "[Investigator]", "[Investigator%20-%20Full]", "[Issue]", "[Journal]", "[Language]", "[Location%20ID]", "[MeSH%20Major%20Topic]", "[MeSH%20Subheading]", "[MeSH%20Subheading]", "[Other%20Term]", "[Pagination]", "[Pharmacological%20Action]", "[Publication%20Type]", "[Publisher]", "[Secondary%20Source ID]", "[Supplementary%20Concept]", "[Text%20Word]", "[Title]", "[Title/Abstract]", "[Transliterated%20Title]", "[Volume]"};

    //String for requests

    string request;
    string sBaseRequest;
    string sDatabase;
    string sBasicSearching;
    string sBasicRequest;
    string sBasicCitation;
    string sSpaceCit;
    string sSpaceWords;
    string sAnd;
    string sOr;
    string sTerm;

    ofxJSONElement myData;
};

#endif /* defined(__httpRequestPubMed__ofxPubMed__) */

////////////////////////////////////////////////////////////////
//Manual: http://www.ncbi.nlm.nih.gov/books/NBK25499/#chapter4.ESearch
////////////////////////////////////////////////////////////////
/* INPUT
 
 eutils/tool: Name of application making the E-utility call. Value must be a string with no internal spaces.
 
 RESUME of tools:
 
 EInfo DTD: eutils/einfo.fcgi
 * Provides a list of the names of all valid Entrez databases.
 * Provides statistics for a single database, including lists of indexing fields and available link names.
 
 ESearch DTD: eutils/esearch.fcgi
 * Provides a list of UIDs matching a text query
 * Posts the results of a search on the History server
 * Downloads all UIDs from a dataset stored on the History server
 * Combines or limits UID datasets stored on the History server
 * Sorts sets of UIDs
 
 EPost DTD: eutils/epost.fcgi
 * Uploads a list
 
 ESummary DTD: eutils/esummary.fcgi
 * Returns docs
 
 (extra) EFetch: eutils/efetch.fcgi
 * Returns formatted data records
 
 ELink DTD: eutils/elink.fcgi
 * Returns UIDs links..
 
 EGQuery DTD: eutils/egquery.fcgi
 * Provides the number of records retrieved in all Entrez databases by a single text query.
 
 (extra) Ecitmatch: eutils/ecitmatch.cgi
 
 ESpell DTD (Retrieves PubMed IDs (PMIDs))
 
 ////////////////////////////////////////////////////////////////
 //SEARCHING PARAMS
 -----------------------------------
 Basic Searching
 -----------------------------------
 esearch.fcgi?db=<database>&term=<query>
 
 Example: Get the PubMed IDs (PMIDs) for articles about breast cancer published in Science in 2008
 
 http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=science[journal]+AND+breast+cancer+AND+2008[pdat]
 
 Types of search param:
 
 [Alliation]
 [All fields] // default
 [Author]
 [Author-Corporate]
 [Author-First]
 [Author - Full]
 [Author - Identifier]
 [Author - Last]
 [Book]
 [Date - Completion]
 [Date - Create]
 [Date - Entrez]
 [Date - MeSH]
 [Date - Modification]
 [Date - Publication]
 [EC/RN Number]
 [Editor]
 [Filter]
 [Grant Number]
 [ISBN]
 [Investigator]
 [Investigator - Full]
 [Issue]
 [Journal]
 [Language]
 [Location ID]
 [MeSH Major Topic]
 [MeSH Subheading]
 [MeSH Subheading]
 [Other Term]
 [Pagination]
 [Pharmacological Action]
 [Publication Type]
 [Publisher]
 [Secondary Source ID]
 [Supplementary Concept]
 [Text Word]
 [Title]
 [Title/Abstract]
 [Transliterated Title]
 [Volume]
 
 -----------------------------------
 Optional Parameters – History Server
 -----------------------------------
 usehistory:
 ESearch will post the UIDs resulting from the search operation onto the History server
 Set to 'y'
 
 
 WebEnv:
 Web environment string returned from a previous ESearch
 Set to 'y'
 >> esearch.fcgi?db=pubmed&term=asthma&WebEnv=<webenv string>&usehistory=y
 
 *** query_key: ***
 
 Integer query key returned by a previous ESearch, EPost or ELink call. When provided, ESearch will find the intersection of the set specified by query_key and the set retrieved by the query in term (i.e. joins the two with AND). For query_key to function, WebEnv must be assigned an existing WebEnv string and usehistory must be set to 'y'.
 
 Values for query keys may also be provided in term if they are preceeded by a '#' (%23 in the URL). While only one query_key parameter can be provided to ESearch, any number of query keys can be combined in term. Also, if query keys are provided in term, they can be combined with OR or NOT in addition to AND.
 
 The following two URLs are functionally equivalent:
 
 esearch.fcgi?db=pubmed&term=asthma&query_key=1&WebEnv=
 <webenv string>&usehistory=y
 
 esearch.fcgi?db=pubmed&term=%231+AND+asthma&WebEnv=
 <webenv string>&usehistory=y
 
 -----------------------------------
 Optional Parameters – Retrieval
 -----------------------------------
 retmax:
 Total number of UIDs from the retrieved set to be shown in the XML output (default = 20)
 
 field:
 If used, the entire search term will be limited to the specified Entrez field
 >> esearch.fcgi?db=pubmed&term=asthma&field=title
 >> esearch.fcgi?db=pubmed&term=asthma[title]
 
 -----------------------------------
 Optional Parameters – Dates
 -----------------------------------
 datetype:
 Type of date used to limit a search.
 common values are 'mdat' (modification date), 'pdat' (publication date) and 'edat' (Entrez date)
 
 reldate:
 When reldate is set to an integer n, the search returns only those items that have a date specified by datetype within the last n days.
 
 mindate, maxdate:
 Date range used to limit a search result
 
 Examples:
 http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=cancer&reldate=60&datetype=edat&retmax=100&usehistory=y
 
 http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=PNAS[ta]+AND+97[vi]&retstart=6&retmax=6&tool=biomed3
 
 http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=nlmcatalog&term=obstetrics+AND+ncbijournals[filter]
 
 -----------------------------------
 Searching PubMed with Citation Data
 -----------------------------------
 ecitmatch.cgi?db=pubmed&rettype=xml&bdata=<citations>
 
 Input: List of citation strings separated by a carriage return (%0D)
 
 Example: Search PubMed for the following ciations:
 
 Art1: Mann, BJ. (1991) Proc. Natl. Acad. Sci. USA. 88:3248
 
 Art2: Palmenberg, AC. (1987) Science 235:182
 
 http://eutils.ncbi.nlm.nih.gov/entrez/eutils/ecitmatch.cgi?db=pubmed&retmode=xml&bdata=proc+natl+acad+sci+u+s+a|1991|88|3248|mann+bj|Art1|%0Dscience|1987|235|182|palmenberg+ac|Art2|
 
 */

////////////////////////////////////////////////////////////////
/*
 OUTPUT
 
 Sample ESearch Output
 
 <?xml version="1.0" ?>
 <!DOCTYPE eSearchResult PUBLIC "-//NLM//DTD eSearchResult, 11 May 2002//EN"
 "http://www.ncbi.nlm.nih.gov/entrez/query/DTD/eSearch_020511.dtd">
 <eSearchResult>
 <Count>255147</Count>   # total number of records matching query
 <RetMax>20</RetMax># number of UIDs returned in this XML; default=20
 <RetStart>0</RetStart># index of first record returned; default=0
 <QueryKey>1</QueryKey># QueryKey, only present if &usehistory=y
 <WebEnv>0l93yIkBjmM60UBXuvBvPfBIq8-9nIsldXuMP0hhuMH-
 8GjCz7F_Dz1XL6z@397033B29A81FB01_0038SID</WebEnv>
 # WebEnv; only present if &usehistory=y
 <IdList>
 <Id>229486465</Id>    # list of UIDs returned
 <Id>229486321</Id>
 <Id>229485738</Id>
 <Id>229470359</Id>
 <Id>229463047</Id>
 <Id>229463037</Id>
 <Id>229463022</Id>
 <Id>229463019</Id>
 <Id>229463007</Id>
 <Id>229463002</Id>
 <Id>229463000</Id>
 <Id>229462974</Id>
 <Id>229462961</Id>
 <Id>229462956</Id>
 <Id>229462921</Id>
 <Id>229462905</Id>
 <Id>229462899</Id>
 <Id>229462873</Id>
 <Id>229462863</Id>
 <Id>229462862</Id>
 </IdList>
 <TranslationSet>        # details of how Entrez translated the query
 <Translation>
 <From>mouse[orgn]</From>
 <To>"Mus musculus"[Organism]</To>
 </Translation>
 </TranslationSet>
 <TranslationStack>
 <TermSet>
 <Term>"Mus musculus"[Organism]</Term>
 <Field>Organism</Field>
 <Count>255147</Count>
 <Explode>Y</Explode>
 </TermSet>
 <OP>GROUP</OP>
 </TranslationStack>
 <QueryTranslation>"Mus musculus"[Organism]</QueryTranslation>
 </eSearchResult>
 */

////////////////////////////////////////////////////////////////
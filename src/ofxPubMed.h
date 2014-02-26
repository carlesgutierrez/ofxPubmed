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
//#include "ofxUI.h"
#include "guiPubMed.h"

#define MAXITEMS 35
#define MAXITEMSDATAS 6
#define TEXTLINEHEIGHT 24

class ofxPubMed {
    
public:
    
    ofxPubMed();
    ~ofxPubMed();
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    void applyRequest();
    
    
    //Search ID Functions
    void changeBasicSearchRequest(string basicSearch);
    void setBasiceSearchRequest();
    void starteSearchRequestWithItem(string item, string addtype);
    void addANDSimpleTagRequest(string newitem, string addtype);
    void addORSimpleTagRequest(string newitem, string addtype);
    void addConsecutiveTagRequest(string newitem, string addtype);
    void addDataTagRequest(string fromdata, string todata, string type);
    void addDataTypeRequest(string datatype);
    void addRelDateRequest(string reldate, string days);
    void addMinMaxDataSearchRequest(string datemin, string typedatemin, string datemax, string typedatemax);

    string setformatForSearch(string text);

private:
	
    //USED IN REQUEST
    string myRequestSelItemsArray[MAXITEMS] = {"[Alliation]","[All%20Fields]", "[Author]", "[Author%20-%20Corporate]", "[Author%20-%20First]", "[Author%20-%20Full]", "[Author%20- Identifier]", "[Author%20-%20Last]", "[Book]", "[EC/RN%20Number]", "[Editor]", "[Filter]", "[Grant%20Number]", "[ISBN]", "[Investigator]", "[Investigator%20-%20Full]", "[Issue]", "[Journal]", "[Language]", "[Location%20ID]", "[MeSH%20Major%20Topic]", "[MeSH%20Subheading", "[Other%20Term]", "[Pagination]", "[Pharmacological%20Action]", "[Publication%20Type]", "[Publisher]", "[Secondary%20Source ID]", "[Supplementary%20Concept]", "[Text%20Word]", "[Title]", "[Title/Abstract]", "[Transliterated%20Title]", "[Volume]"};
    vector<string> myRequestSelItems;
    
    string myRequestDataSelItemsArray[MAXITEMSDATAS] = { "[DCOM]", "[DA]", "[EDAT]","[MHDA]", "[Date%20-%20Modification]", "[DP]",};
    vector<string> myRequestDataSelItems;
/*
    Date Completed (DCOM)
    Date Created (DA)
    Date Last Revised (LR)
    Date of Electronic Publication (DEP)
    Date of Publication (DP)
    Entrez Date (EDAT)
    MeSH Date (MHDA)
*/
    
    //String for requests

    string request;
    string sBaseRequest;
    string sDatabase;
    string sBasicSearching;
    string sBasicRequest;
    string sBasicCitation;

    string sRelDate;
    string sDateType;
    string sRetMax;
    string sUseHist;
    
    string sSpaceCit;
    string sSpaceWords;
    string sAnd;
    string sOr;
    string sNot;
    
    string sTerm;
    string sSlash;
    string sQuotes;
    
    string sDocFetch;
    string sId;
    
    string sdataType;
    string sMindate;
    string sMaxdate;
    
    bool bHitRequest;
    bool parsingSuccessful;

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
 
 EFetch: eutils/efetch.fcgi
 * Returns formatted data records
 
 ELink DTD: eutils/elink.fcgi
 * Returns UIDs links..
 
 EGQuery DTD: eutils/egquery.fcgi
 * Provides the number of records retrieved in all Entrez databases by a single text query.
 
 Ecitmatch: eutils/ecitmatch.cgi
 * Retrieves PubMed IDs (PMIDs) that correspond to a set of input citation strings.
 
 ESpell DTD (Retrieves PubMed IDs (PMIDs))
 
 ////////////////////////////////////////////////////////////////
 //SEARCHING PARAMS
 
 * ESearch: Base URL http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi
 
 Functions:
 - Provides a list of UIDs matching a text query
 - Posts the results of a search on the History server
 - Downloads all UIDs from a dataset stored on the History server
 - Combines or limits UID datasets stored on the History server
 - Sorts sets of UIDs
 
 //Required Parameters
 db: Database to search. Value must be a valid Entrez database name (default = pubmed).
 term: Entrez text query. All special characters must be URL encoded. Spaces may be replaced by '+' signs. For very long queries (more than several hundred characters long), consider using an HTTP POST call. See the PubMed or Entrez help for information about search field descriptions and tags. Search fields and tags are database specific.

 //Optional Parameters Ð [ History Server ]
 
 (NIY)usehistory: When usehistory is set to 'y' (NIY = Not implemented yet)
 (NIY)WebEnv: Web environment string returned from a previous ESearch (NIY)
 
 (NIY)query_key:Integer query key returned by a previous ESearch, EPost or ELink call. When provided, ESearch will find the intersection of the set specified by query_key and the set retrieved by the query in term (i.e. joins the two with AND).For query_key to function, WebEnv must be assigned an existing WebEnv string and usehistory must be set to 'y'.
 
 //Optional Parameters Ð [ Retrieval ]
 
 //Optional Parameters Ð [ Dates ]
 
 Datetype: Type of date used to limit a search. The allowed values vary between Entrez databases, but common values are 'mdat' (modification date), 'pdat' (publication date) and 'edat' (Entrez date). Generally an Entrez database will have only two allowed values for datetype.

 reldate: When reldate is set to an integer n, the search returns only those items that have a date specified by datetype within the last n days.
 
 mindate, maxdate: Date range used to limit a search result by the date specified by datetype. These two parameters (mindate, maxdate) must be used together to specify an arbitrary date range. The general date format is YYYY/MM/DD, and these variants are also allowed: YYYY, YYYY/MM.

 
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
 Optional Parameters â€“ History Server
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
 Optional Parameters â€“ Retrieval
 -----------------------------------
 retmax:
 Total number of UIDs from the retrieved set to be shown in the XML output (default = 20)
 
 field:
 If used, the entire search term will be limited to the specified Entrez field
 >> esearch.fcgi?db=pubmed&term=asthma&field=title
 >> esearch.fcgi?db=pubmed&term=asthma[title]
 
 -----------------------------------
 Optional Parameters â€“ Dates
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
 PUBMED ELEMENTS ( Field	Abbreviation )
 From: http://www.nlm.nih.gov/bsd/mms/medlineelements.html
 
 Abstract 	(AB)
 Copyright Information (CI)
 Affiliation (AD)
 Investigator Affiliation (IRAD)
 Article Identifier (AID)
 Author (AU)
 Author Identifier 	(AUID)
 Full Author (FAU)
 Book Title 	(BTI)
 Collection Title 	(CTI)
 Comments/Corrections
 Corporate Author (CN)
 Create Date 	(CRDT)

 Date Completed (DCOM)
 Date Created (DA)
 Date Last Revised (LR)
 Date of Electronic Publication (DEP)
 Date of Publication (DP)
 Entrez Date (EDAT)
 MeSH Date (MHDA)
 
 Edition 	(EN)
 Editor and Full Editor Name 	(ED) (FED)

 Gene Symbol (GS)
 
 General Note (GN)
 Grant Number 	(GR)
 Investigator Name and Full Investigator Name (IR) (FIR)
 ISBN 	(ISBN)
 ISSN (IS)
 Issue (IP)
 Journal Title Abbreviation 	(TA)
 Journal Title 	(JT)
 Language (LA)
 Location Identifier 	(LID)
 Manuscript Identifier 	(MID)

 MeSH Terms(MH)
 NLM Unique ID (JID)
 Number of References (RF)

 Other Abstract and Other Abstract Language 	(OAB)(OABL)
 Other Copyright Information (OCI)
 Other ID (OID)
 Other Term (OT)
 Other Term Owner (OTO)
 Owner (OWN)
 
 Field	Abbreviation
 Pagination 	(PG)
 Personal Name as Subject(PS)
 Full Personal Name as Subject 	(FPS)
 Place of Publication 	(PL)
 Publication History Status(PHST)
 Publication Status(PST)
 Publication Type(PT)
 Publishing Model(PUBM)
 PubMed Central Identifier 	(PMC)
 PubMed Central Release 	(PMCR)
 PubMed Unique Identifier (PMID)
 Registry Number/EC Number (RN)
 Substance Name (NM)
 Secondary Source ID (SI)
 Source (SO)
 Space Flight Mission (SFM)
 Status (STAT)
 Subset (SB)
 Title (TI)
 Transliterated Title (TT)
 Volume (VI)
 Volume Title (VTI)
 */

////////////////////////////////////////////////////////////////

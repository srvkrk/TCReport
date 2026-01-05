#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <tccore/custom.h>
#include <ict/ict_userservice.h>
#include <tc/preferences.h>
#include <lov/lov_msg.h>
#include <ss/ss_errors.h>
#include <sa/user.h>
#include <tccore/tc_msg.h>
#include <ae/dataset_msg.h>
#include <tc/emh.h>
#include <ecm/ecm.h>
#include <fclasses/tc_string.h>
#include <tccore/item_errors.h>
#include <sa/tcfile.h>
#include <tcinit/tcinit.h>
#include <tccore/tctype.h>
#include <time.h>
#include <ae/ae.h>                  
#include <setjmp.h>
#include <ae/ae_errors.h>           
#include <ae/ae_types.h>           
#include <unidefs.h>
#include <user_exits/user_exit_msg.h>
#include <pom/enq/enq.h>
#include <ug_va_copy.h>
#include <tie/tie_errors.h>
#include <tccore/grm.h>
#include <tccore/grmtype.h>
#include <tc/tc_startup.h>
#include <user_exits/user_exits.h>
#include <tccore/method.h>
#include <property/prop.h>
#include <property/prop_msg.h>
#include <property/prop_errors.h>
#include <tccore/item.h>
#include <lov/lov.h>
#include <sa/sa.h>
#include <sa/site.h>
#include <res/res_itk.h>
#include <res/reservation.h>
#include <tccore/workspaceobject.h>
#include <tc/wsouif_errors.h>
#include <tccore/aom.h>
#include <publication/dist_user_exits.h>
#include <form/form.h>
#include <epm/epm.h>
#include <epm/epm_task_template_itk.h>
#include <constants/constants.h>
#include <sa/groupmember.h>
#include <bom/bom.h>
#include <cfm/cfm.h>
#include <pie/pie.h>
#include <bom/bom_attr.h>
#include <bom/bom_tokens.h>
#include <tc/envelope.h>
#include <ctype.h>
#include <epm/cr.h>
#include <tc/folder.h>
#include <pom/pom/pom.h>
#include <ps/ps.h>
#include <pie/pie.h> 
#include <tccore/uom.h>
#include <rdv/arch.h>
#include <textsrv/textserver.h>
#include <ae/dataset.h>
#include <assert.h>
#include <stdio.h>
#include <ics/ics2.h>
#include <ics/ics.h>
#include <tccore/item_msg.h>
#include <tccore/aom_prop.h>
#include <tccore/grm_msg.h>
#define CALLAPI(expr)ITKCALL(ifail = expr); if(ifail != ITK_ok) {  return ifail;}
#define ITK_errStore 91900002
#define MAX_LINE_LENGTH 1000
#define Debug TRUE
int status =0;
#define ITK_CALL(X) 							\
		if(Debug)								\
		{										\
			printf(#X);							\
		}										\
		fflush(NULL);							\
		status=X; 								\
		if (status != ITK_ok ) 					\
		{										\
			int				index = 0;			\
			int				n_ifails = 0;		\
			const int*		severities = 0;		\
			const int*		ifails = 0;			\
			const char**	texts = NULL;		\
												\
			EMH_ask_errors( &n_ifails, &severities, &ifails, &texts);		\
			printf("\t%3d error(s)\n", n_ifails);							\
			for( index=0; index<n_ifails; index++)							\
			{																\
				printf("\tError #%d, %s\n", ifails[index], texts[index]);	\
			}																\
			/*return status;*/													\
		}																	\
		else									\
		{										\
			if(Debug)							\
			printf("\tSUCCESS\n");				\
		}										\

int ICS_keylov_get_keylov (const char *key_lov_id, char **key_lov_name, int *options, int *n_lov_entries, char ***lov_keys, char ***lov_values, logical **deprecated_staus, char **owning_site, int *n_shared_sites, char ***shared_sites);
int ICS_describe_unct (int unctNo, char **unctName, char **shortName, char **unctUnit, int *unctFormat);
int DATE_date_to_string (date_t date_struct, const char *format_str, char **date_str);

FILE *Report = NULL;
int ctr = 0;
void write2xml(FILE *Report , char* str)
{
	fprintf(Report,str);
	ctr++;
}
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0) 
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

char* subString (char* mainStringf ,int fromCharf,int toCharf)
{
	int i;
	char *retStringf;
	retStringf = (char*) malloc(200);
	for(i=0; i < toCharf; i++ )
              *(retStringf+i) = *(mainStringf+i+fromCharf);
	*(retStringf+i) = '\0';
	return retStringf;
}

char* TC_ERC_DTReleased(tag_t PartRev_tag)
{
	int	status = 0;
	tag_t *Stat_list = NULLTAG;
	tag_t Stat_tag = NULLTAG;
	int Stat_Cnt = 0;
	char *RlzStatusName = NULL;
	char *Dt_Rlzd = NULL;
	char *Dt_RlzdDup = NULL;
	int j = 0;
	
    ITK_CALL(WSOM_ask_release_status_list(PartRev_tag,&Stat_Cnt,&Stat_list));
    for(j=0;j<Stat_Cnt;j++)
	{
		Stat_tag = Stat_list[j];
		ITK_CALL(AOM_ask_name(Stat_tag, &RlzStatusName));
		printf("\n Part`s Release Status Name: [%s]\n",RlzStatusName);fflush(stdout);
        if ((tc_strcmp(RlzStatusName,"T5_LcsRlzd")==0) || (tc_strcmp(RlzStatusName,"T5_LcsErcRlzd")==0))
		{
			ITK_CALL(AOM_UIF_ask_value(Stat_tag,"date_released",&Dt_Rlzd));
			printf(" \n ERC-Release Status Date: [%s]\n",Dt_Rlzd);fflush(stdout);
             
		}
	}
	if(tc_strlen(Dt_Rlzd)>0)
	{
	   tc_strdup(Dt_Rlzd,&Dt_RlzdDup);
	}
	else
	{
	   tc_strdup("Not_ERC_Released",&Dt_RlzdDup);
	}
	return Dt_RlzdDup;
}

int getClsValueFrmICSTag( tag_t  IcsClsTag , char *clsKeyAtrrId,char **AttrVal)
{
	tag_t objTypeTag=NULLTAG;
	tag_t objTypeTag2=NULLTAG;
	//char   Ptype_name[TCTYPE_name_size_c+1];
	char	*Ptype_name		=	NULL;
	char   Stype_name[TCTYPE_name_size_c+1];
	char   relation_name[TCTYPE_name_size_c+1];
	char   *username  = NULL;
	char *RetAttrVal=NULL;
	char *AttrKeyValue=NULL;
	int       st_count=0;
	int iStCnt				=	0;
	int		status;
	int  ifail = ITK_ok;
	int cnt		=0;
	int lcstatcnt =0;
	tag_t *ClsObjTag = NULLTAG;
	tag_t*    status_list;
	
	

	if(TCTYPE_ask_object_type(IcsClsTag,&objTypeTag));
	//if(TCTYPE_ask_name(objTypeTag,Ptype_name));
	if(TCTYPE_ask_name2(objTypeTag,&Ptype_name));  // TC 14.3 API Change
	//printf("\n getClsValueFrmICSTag IcsClsTag  Ptype_name :: %s\n", Ptype_name); fflush(stdout);

	
	//Create Relation between Intent and Vehicle.
	int partRevCnt=0;
    tag_t* partRevTagObjs = NULLTAG;
    tag_t partRevTag = NULLTAG;
	if(IcsClsTag!=NULLTAG)
	{
		    char * 	theClassId = NULL;
			int  	theAttributeCount;
			int * 	theAttributeIds;
			int * 	theAttributeValCounts;
			char ** 	theAttributeValues;
			tag_t 	theICOTag=NULLTAG;
			printf("\n  input clsKeyAtrrId[%s]",clsKeyAtrrId); fflush(stdout);
			char keyPrefix[10];
			tc_strcpy(keyPrefix,"-");
			tc_strcat(keyPrefix,clsKeyAtrrId);
			printf("\n  input keyPrefix[%s]",keyPrefix); fflush(stdout);
			const char * 	key_lov_id=keyPrefix; //cls attr id for ChassisTypeNo_TYP_APPRVL_NO
			char * 	key_lov_name;
			int  	options;
			int q = 0;
			int keyfound=0;
			int  	n_lov_entries;
			char ** 	lov_keys;
			char ** 	lov_values;
			logical * 	deprecated_staus;
			char * 	owning_site;
			char *keyLovOfCCVNo=(char*) MEM_alloc( 1 * sizeof(lov_keys) );
			int  	n_shared_sites;
			char ** 	shared_sites ;
			theICOTag=IcsClsTag;
			//CALLAPI(ICS_ask_attribute_value(theICOTag,"8066",&AttrKeyValue))
			if(ICS_ask_attribute_value(IcsClsTag,clsKeyAtrrId,&AttrKeyValue))
			
			printf("\n AttrKeyValue: [%s]  key_lov_id: [%s]",AttrKeyValue,key_lov_id); fflush(stdout);
			
			if(AttrKeyValue)
			{
				*AttrVal = AttrKeyValue;
			
			    if(ICS_keylov_get_keylov(key_lov_id,&key_lov_name,&options,&n_lov_entries,&lov_keys,&lov_values,&deprecated_staus,&owning_site,&n_shared_sites,&shared_sites));
			    //CALLAPI(ICS_keylov_get_keylov(key_lov_id,&key_lov_name,&options,&n_lov_entries,&lov_keys,&lov_values,&deprecated_staus,&owning_site,&n_shared_sites,&shared_sites));
			    printf("\n key_lov_name: [%s] n_lov_entries: [%d] options: [%d]",key_lov_name,n_lov_entries,options); fflush(stdout);
 				for(q=0;q<n_lov_entries;q++)								
				{
					printf("\n lov_keys: [%s] lov_values: [%s]",lov_keys[q],lov_values[q]);fflush(stdout);
					
					if(tc_strcasecmp(AttrKeyValue,lov_keys[q])==0)
					{
						printf("\n Mascot lov_keys: [%s] lov_values: [%s]",lov_keys[q],lov_values[q]);fflush(stdout);
						
						if(lov_values[q])
						{
							tc_strdup(lov_values[q],&RetAttrVal);
						}
						*AttrVal=RetAttrVal;
						break;
					}	
				} 
			}
			else
			{
				*AttrVal="";
				return ITK_ok;
			}
	}
    printf("\n @@@@@@@@@@@@@@@@@@@@@@");fflush(stdout);	
	printf("\n RetAttrVal: [%s]",RetAttrVal);fflush(stdout);
	printf("\n @@@@@@@@@@@@@@@@@@@@@@");fflush(stdout);	
			
	return ITK_ok;
}

int ITK_user_main(int argc,char* argv[]) 
{
	char *message;
	char *loggedInUser = NULL;
	char *sr_no_str = NULL;
	char *item_id_str = NULL;
	char *item_rev_str = NULL;
	char *item_seq_str = NULL;
	char *sr_no_strDup = NULL;
	char *item_id_strDup = NULL;
	char *item_rev_strDup = NULL;
	char *item_seq_strDup = NULL;
	FILE *fpPart_List = NULL;
	char Buffer[MAX_LINE_LENGTH];
	tag_t tItemobj = NULLTAG;
	int n_entries = 2;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	char *Product = NULL;
	char *ProductDup = NULL;
	char *DRStatus = NULL;
	char *DRStatusDup = NULL;
	char *Platform = NULL;
	char *PlatformDup = NULL;
	char *cItem_Desc = NULL;
	char *cItem_DescDup = NULL;
	int i = 0;
	char *RptFile = (char *) malloc(400*sizeof(char));
	char *item_revseq_strDup = (char *) malloc(50*sizeof(char));
	char *ERCRlzdDt = NULL;
	FILE *fpOutput_file = NULL;
	tag_t DesRev_tag = NULLTAG;
	char *inp_email_str = NULL;
	char *inp_email_strDup = NULL;
    
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");fflush(stdout);	
	ITK_CALL(ITK_initialize_text_services( ITK_BATCH_TEXT_MODE ));
	ITK_CALL(ITK_set_journalling( TRUE ));
    status = ITK_auto_login ();	
    if (status != ITK_ok ) 
	{
        EMH_ask_error_text(status, &message);
        printf(" Error with ITK_auto_login: \"%d\", \"%s\"\n", status, message);
        MEM_free(message);
        return status;
    }
	else
	{
		printf(" Auto Login Successfull\n");fflush(stdout);
		POM_get_user_id(&loggedInUser);
		printf(" Logged in User: [%s]\n",loggedInUser);fflush(stdout);
	}
	
	char GenDate[100] = "";
	time_t 	now;
	struct 	tm when;
	time(&now);
	when = *localtime(&now);
	strftime(GenDate,100,"%d_%b_%Y_%H_%M_%S",&when);
	printf(" Current TimeStamp: [%s]\n", GenDate);fflush(stdout);
	
	inp_email_str = ITK_ask_cli_argument("-Email=");
	trimwhitespace(inp_email_str);
	if(inp_email_str!=NULL)tc_strdup(inp_email_str,&inp_email_strDup);
	printf(" [1]: Input User Email(inp_email_strDup): [%s]\n",inp_email_strDup);
	
	printf("\n Generating Report File Name..!!");fflush(stdout);
	tc_strcpy(RptFile,"Vehicle_CRVC_Details_Rpt_File");
	tc_strcat(RptFile,"_");
	tc_strcat(RptFile,GenDate);
	tc_strcat(RptFile,".csv");
	printf("\n Report File Name: [%s]", RptFile);fflush(stdout);
	printf("\n Report File Generated..!!");fflush(stdout);

	fpPart_List = fopen("/proj/PLMLoading/UAFiles/ProE_Downloading/CVPROD/CV_VehicleDetails/PartList.txt","r");
	
	char *PreVCompFile = (char *) malloc(100*sizeof(char));
	printf("\n Generating XML Report File Name..!!");fflush(stdout);
	tc_strcpy(PreVCompFile,"/tmp/");
	tc_strcat(PreVCompFile,"VehicleDetailsReport");
	tc_strcat(PreVCompFile,"_");
	tc_strcat(PreVCompFile,GenDate);
	tc_strcat(PreVCompFile,".xml");
	//Report = fopen("/tmp/VehicleDetailsReport.xml","w");
	printf("\n Pre Vehicle Details Report File Name: [%s]", PreVCompFile);fflush(stdout);
	
	Report = fopen(PreVCompFile,"w");
	if(Report == NULL)
	{
		printf("ERROR: Unable To Open XML File..!!\n");
	}
	else
	{
		printf("XML File Opened Successfully..!!\n");
	}
	write2xml(Report,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	write2xml(Report,"<DetailsRpt>\n");
	
    fpOutput_file = fopen(RptFile, "w");
    fprintf(fpOutput_file,"SR_NO, VEHICLE/CRVC_NO, REV, SEQ, VEHICLE_DESCRIPTION, LATEST_RELEASED_MOD_GATEWAY, PRODUCT_LINE, PLATFORM, ERC_RELEASE_DATE, [VC]CUSTOMER(CUSTOMER), [VC]FUEL(FUEL)\n");fflush(fpOutput_file); 
	if(fpOutput_file == NULL)
	{
	    printf("\n Unable to Create Report File: --------> [%s]",RptFile);fflush(stdout);
		return 0;
	}
	if(fpPart_List != NULL)
	{
		printf(" Input_File Not Null..!!\n");fflush(stdout);
		while(fgets(Buffer,MAX_LINE_LENGTH,fpPart_List)!=NULL)
		{
			sr_no_str=strtok(Buffer,"^");
			item_id_str=strtok(NULL,"^");
			item_rev_str=strtok(NULL,"^");
			item_seq_str=strtok(NULL,"^");
			
			if(sr_no_str!=NULL)tc_strdup(sr_no_str,&sr_no_strDup);
			if(item_id_str!=NULL)tc_strdup(item_id_str,&item_id_strDup);
			if(item_rev_str!=NULL)tc_strdup(item_rev_str,&item_rev_strDup);
			if(item_seq_str!=NULL)tc_strdup(item_seq_str,&item_seq_strDup);
			
			if(sr_no_strDup!=NULL)trimwhitespace(sr_no_strDup);
			if(item_id_strDup!=NULL)trimwhitespace(item_id_strDup);
			if(item_rev_strDup!=NULL)trimwhitespace(item_rev_strDup);
			if(item_seq_strDup!=NULL)trimwhitespace(item_seq_strDup);
			
			tc_strcpy(item_revseq_strDup,item_rev_strDup);
			tc_strcat(item_revseq_strDup,";");
			tc_strcat(item_revseq_strDup,item_seq_strDup);
			
			printf("\n Sr. No(sr_no_strDup): [%s]\n",sr_no_strDup);
			printf("\n Part No(item_id_strDup): [%s]\n",item_id_strDup);
			printf("\n Part Rev(item_rev_strDup): [%s]\n",item_rev_strDup);
			printf("\n Part Seq(item_seq_strDup): [%s]\n",item_seq_strDup);
			printf("\n Part Rev&Seq(item_revseq_strDup): [%s]\n",item_revseq_strDup);
			ITK_CALL(QRY_find2("DesignRevision Sequence",&tItemobj));
            if(tItemobj != NULLTAG)
			{
				printf("\n DesignRevision Sequence Found Successfully..!!\n");fflush(stdout);
				char *cEntries[2]  = {"Revision","ID"};
				char *cValues[2]  = {item_revseq_strDup,item_id_strDup};
				//char *cValues[2]  = {"A;2","5137D1D0270001_WE"};
			    ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
				printf("\n -----------------------------------------------\n");fflush(stdout);
				printf("\n No of Revision Found: [%d]\n",n_itemobj_found);fflush(stdout);
			    printf("\n -----------------------------------------------\n");fflush(stdout);
				if(n_itemobj_found > 0)
				{
					printf(" Quiried Design Revision & Sequence Found..!!\n");fflush(stdout);
					for (i = 0; i < n_itemobj_found; i++)
					{
						DesRev_tag = titemobj_results[i];
						if((tc_strlen(item_id_strDup)==9) || (tc_strlen(item_id_strDup)==12))
						{
							printf("\n Function1: ERC-Release Date Find Start");fflush(stdout);
							ERCRlzdDt = TC_ERC_DTReleased(DesRev_tag);
							printf("\n Function1: ERC-Release Date Find End\n");fflush(stdout);
							ITK_CALL(AOM_ask_value_string(titemobj_results[i],"t5_PartStatus",&DRStatus));
							if(tc_strlen(DRStatus)>0)
							{
								tc_strdup(DRStatus,&DRStatusDup);
							}
							else
							{
								tc_strdup("--",&DRStatusDup);
								printf("\n DR Status Value is NULL..!!");fflush(stdout);
							}
							ITK_CALL(AOM_ask_value_string(titemobj_results[i],"t5_Product",&Product));
							if(tc_strlen(Product)>0)
							{
								tc_strdup(Product,&ProductDup);
							}
							else
							{
								tc_strdup("--",&ProductDup);
								printf("\n Product Line Value is NULL..!!");fflush(stdout);
							}
							ITK_CALL(AOM_ask_value_string(titemobj_results[i],"t5_Platform",&Platform));
							if(tc_strlen(Platform)>0)
							{
								tc_strdup(Platform,&PlatformDup);
							}
							else
							{
								tc_strdup("--",&PlatformDup);
								printf("\n Platform Value is NULL..!!");fflush(stdout);
							}
							ITK_CALL(AOM_ask_value_string(titemobj_results[i],"object_desc",&cItem_Desc));
							printf("\n Item Description Before Dup & Trim: ---> <%s> \n",cItem_Desc);fflush(stdout);
							if(tc_strlen(cItem_Desc)>0)
							{
								tc_strdup(cItem_Desc,&cItem_DescDup);
							}
							else
							{
								tc_strdup("--",&cItem_DescDup);
								printf("\n Item Description Value is NULL..!!");fflush(stdout);
							}
							trimwhitespace(cItem_DescDup);
							printf("\n Item Description Value After Dup & Trim: --------> <%s>", cItem_DescDup);fflush(stdout);
							STRNG_replace_str(cItem_DescDup,","," ",&cItem_DescDup);
							STRNG_replace_str(cItem_DescDup,";"," ",&cItem_DescDup);
							STRNG_replace_str(cItem_DescDup,"\n"," ",&cItem_DescDup);
							STRNG_replace_str(cItem_DescDup,"'"," ",&cItem_DescDup);
							printf("\n Item Description Final Value: --------> [%s]\n", cItem_DescDup);fflush(stdout);
							
							printf("\n Function2: Classification Attribute Find Start");fflush(stdout);
							tag_t Vc_spec_relation_type = NULLTAG;
							int vcspec_count_f = 0;
							tag_t* Vc_specObjects_f = NULLTAG;
							char *vcspec_item_id_f = NULL;
							char *vcclass_f = NULL;
							tag_t VehMstrTag = NULLTAG;
							int cnt	= 0;
							tag_t *ClsObjTag_results = NULLTAG;
							tag_t ClsObj_f = NULLTAG;
							
							char *customerval = NULL;
							customerval = (char *) malloc(100*sizeof(char));
							char *fuelval = NULL;
							fuelval = (char *) malloc(100*sizeof(char));
							
							if(customerval!=NULL)trimwhitespace(customerval);
							if(fuelval!=NULL)trimwhitespace(fuelval);
						
							ITK_CALL(GRM_find_relation_type("T5_VCSpec",&Vc_spec_relation_type));
							if(Vc_spec_relation_type != NULLTAG)
							{
								ITK_CALL(GRM_list_secondary_objects_only(DesRev_tag, Vc_spec_relation_type, &vcspec_count_f, &Vc_specObjects_f));
								printf("\n ----------------------------------------------");fflush(stdout);
								printf("\n Total Tech_Spech Attached with Vehicle: [%d]",vcspec_count_f);fflush(stdout);
								printf("\n ----------------------------------------------\n");fflush(stdout);
								if(vcspec_count_f > 0)
								{
									ITK_CALL(AOM_ask_value_string(Vc_specObjects_f[0],"item_id",&vcspec_item_id_f));
									printf("\n Tech_Spech No: [%s]\n",vcspec_item_id_f);fflush(stdout);
																			
									ITK_CALL(AOM_ask_value_string(Vc_specObjects_f[0],"t5_VCClassName",&vcclass_f));
									printf("\n Vehicle Class: [%s]",vcclass_f);fflush(stdout);
									
									if(tc_strlen(vcclass_f) > 0)
									{
										char *getcustomerval_id = NULL;
										getcustomerval_id = (char *) malloc(100*sizeof(char));
										char *getfuelval_id = NULL;
										getfuelval_id = (char *) malloc(100*sizeof(char));
										
										if(tc_strcmp(vcclass_f,"MCV")==0)
										{
											printf("\n Attribute_ID Start: [MCV] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"5029");
											tc_strcpy(getfuelval_id,"5037");					
											printf("\n getcustomerval_id_MCV: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_MCV: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [MCV] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"HCV")==0)
										{
											printf("\n Attribute_ID Start: [HCV] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"6029");
											tc_strcpy(getfuelval_id,"6037");						
											printf("\n getcustomerval_id_HCV: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_HCV: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [HCV] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"LCV")==0)
										{
											printf("\n Attribute_ID Start: [LCV] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"4029");
											tc_strcpy(getfuelval_id,"4037");
											printf("\n getcustomerval_id_LCV: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_LCV: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [LCV] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"LMV")==0)
										{
											printf("\n Attribute_ID Start: [LMV] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"2029");
											tc_strcpy(getfuelval_id,"2037");
											printf("\n getcustomerval_id_LMV: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_LMV: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [LMV] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"BUS")==0)
										{
											printf("\n Attribute_ID Start: [BUS] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"7029");
											tc_strcpy(getfuelval_id,"7037");						
											printf("\n getcustomerval_id_BUS: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_BUS: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [BUS] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"UV_VAN")==0)
										{
											printf("\n Attribute_ID Start: [UV_VAN] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"10029");
											tc_strcpy(getfuelval_id,"10037");						
											printf("\n getcustomerval_id_UV_VAN: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_UV_VAN: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [UV_VAN] \n");fflush(stdout);
										}
										else if(tc_strcmp(vcclass_f,"ICV")==0)
										{
											printf("\n Attribute_ID Start: [ICV] \n");fflush(stdout);
											tc_strcpy(getcustomerval_id,"3029");
											tc_strcpy(getfuelval_id,"3037");
											printf("\n getcustomerval_id_ICV: [%s]",getcustomerval_id);fflush(stdout);
											printf("\n getfuelval_id_ICV: [%s]",getfuelval_id);fflush(stdout);
											printf("\n Attribute_ID End: [ICV] \n");fflush(stdout);
										}
										else
										{
											printf("\n VC Class Not Matched..!! \n");fflush(stdout);
										}
										
										ITK_CALL(ITEM_ask_item_of_rev(DesRev_tag,&VehMstrTag));
										ITK_CALL(AOM_ask_value_tags(VehMstrTag,"IMAN_classification",&cnt,&ClsObjTag_results));
										printf("\n Vehicle Master Object Count: [%d]\n", cnt); fflush(stdout);
										if(cnt > 0)
										{
											ClsObj_f=*ClsObjTag_results;	
											ITK_CALL(getClsValueFrmICSTag(ClsObj_f,getcustomerval_id,&customerval));
											ITK_CALL(getClsValueFrmICSTag(ClsObj_f,getfuelval_id,&fuelval));
											
											if(customerval!=NULL)trimwhitespace(customerval);
											if(fuelval!=NULL)trimwhitespace(fuelval);
											
											printf("\n [VC]CUSTOMER(CUSTOMER): [%s]",customerval);fflush(stdout);
											printf("\n [VC]FUEL(FUEL): [%s]",fuelval); fflush(stdout);
										}
										else
										{
											printf("\n VC Master Not Found..!! \n");fflush(stdout);
											tc_strcpy(customerval,"--");
											tc_strcpy(fuelval,"--");
										}				
									}
									else
									{
										printf("\n VC Class Not Found..!! \n");fflush(stdout);
										tc_strcpy(customerval,"--");
										tc_strcpy(fuelval,"--");
									}
								}
								else
								{
									printf("\n No Tech_Spech Attached with Vehicle..!! \n");fflush(stdout);
									tc_strcpy(customerval,"--");
									tc_strcpy(fuelval,"--");
								}
							}
							printf("\n Function2: Classification Attribute Find End");fflush(stdout);
							
							printf(" Vehicle Details Start...!!\n");fflush(stdout);
							printf("[1] Sr_No: [%s]\n",sr_no_strDup);fflush(stdout);
							printf("[2] Vehicle/CRVC_No: [%s]\n",item_id_strDup);fflush(stdout);
							printf("[3] Revision: [%s]\n",item_rev_strDup);fflush(stdout);
							printf("[4] Sequence: [%s]\n",item_seq_strDup);fflush(stdout);
							printf("[5] Description: [%s]\n",cItem_DescDup);fflush(stdout);
							printf("[6] DR/AR Status: [%s]\n",DRStatusDup);fflush(stdout);
							printf("[7] Product_Line: [%s]\n",PlatformDup);fflush(stdout);
							printf("[8] PlatForm: [%s]\n",PlatformDup);fflush(stdout);
							printf("[9] ERC-Release-Date: [%s]\n",ERCRlzdDt);fflush(stdout);
							printf("[10] [VC]CUSTOMER(CUSTOMER): [%s]\n",customerval);fflush(stdout);
							printf("[11] [VC]FUEL(FUEL): [%s]\n",fuelval);fflush(stdout);
							printf(" Vehicle Details End...!!\n");fflush(stdout);
							
							fprintf(fpOutput_file,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",sr_no_strDup,item_id_strDup,item_rev_strDup,item_seq_strDup,cItem_DescDup,DRStatusDup,ProductDup,PlatformDup,ERCRlzdDt,customerval,fuelval);fflush(fpOutput_file);
							
							if(cItem_DescDup != NULL)
							{
								STRNG_replace_str(cItem_DescDup,"&","&amp;",&cItem_DescDup);
								STRNG_replace_str(cItem_DescDup,"<","&lt;",&cItem_DescDup);
								STRNG_replace_str(cItem_DescDup,">","&gt;",&cItem_DescDup);
							}
							if(DRStatusDup != NULL)
							{
								STRNG_replace_str(DRStatusDup,"&","&amp;",&DRStatusDup);
								STRNG_replace_str(DRStatusDup,"<","&lt;",&DRStatusDup);
								STRNG_replace_str(DRStatusDup,">","&gt;",&DRStatusDup);
							}
							if(ProductDup != NULL)
							{
								STRNG_replace_str(ProductDup,"&","&amp;",&ProductDup);
								STRNG_replace_str(ProductDup,"<","&lt;",&ProductDup);
								STRNG_replace_str(ProductDup,">","&gt;",&ProductDup);
							}
							if(PlatformDup != NULL)
							{
								STRNG_replace_str(PlatformDup,"&","&amp;",&PlatformDup);
								STRNG_replace_str(PlatformDup,"<","&lt;",&PlatformDup);
								STRNG_replace_str(PlatformDup,">","&gt;",&PlatformDup);
							}
							if(ERCRlzdDt != NULL)
							{
								STRNG_replace_str(ERCRlzdDt,"&","&amp;",&ERCRlzdDt);
								STRNG_replace_str(ERCRlzdDt,"<","&lt;",&ERCRlzdDt);
								STRNG_replace_str(ERCRlzdDt,">","&gt;",&ERCRlzdDt);
							}
		
							write2xml(Report,"<DataList>\n");
							write2xml(Report,"<SrNo>"); if(tc_strlen(sr_no_strDup)>0) write2xml(Report,sr_no_strDup); else write2xml(Report,"NA"); write2xml(Report,"</SrNo>\n");
							write2xml(Report,"<PartNo>"); if(tc_strlen(item_id_strDup)>0) write2xml(Report,item_id_strDup); else write2xml(Report,"NA"); write2xml(Report,"</PartNo>\n");
							write2xml(Report,"<PartRev>"); if(tc_strlen(item_rev_strDup)>0) write2xml(Report,item_rev_strDup); else write2xml(Report,"NA"); write2xml(Report,"</PartRev>\n");
							write2xml(Report,"<PartSeq>"); if(tc_strlen(item_seq_strDup)>0) write2xml(Report,item_seq_strDup); else write2xml(Report,"NA"); write2xml(Report,"</PartSeq>\n");
							write2xml(Report,"<Desc>"); if(tc_strlen(cItem_DescDup)>0) write2xml(Report,cItem_DescDup); else write2xml(Report,"NA"); write2xml(Report,"</Desc>\n");
							write2xml(Report,"<DRAR>"); if(tc_strlen(DRStatusDup)>0) write2xml(Report,DRStatusDup); else write2xml(Report,"NA"); write2xml(Report,"</DRAR>\n");
							write2xml(Report,"<Prod>"); if(tc_strlen(ProductDup)>0) write2xml(Report,ProductDup); else write2xml(Report,"NA"); write2xml(Report,"</Prod>\n");
							write2xml(Report,"<Plat>"); if(tc_strlen(PlatformDup)>0) write2xml(Report,PlatformDup); else write2xml(Report,"NA"); write2xml(Report,"</Plat>\n");
							write2xml(Report,"<NormalRlzd>"); if(tc_strlen(ERCRlzdDt)>0) write2xml(Report,ERCRlzdDt); else write2xml(Report,"NA"); write2xml(Report,"</NormalRlzd>\n");
							write2xml(Report,"</DataList>\n");
						}
					}
				}
				else
                {
					printf(" DesignRevision Not Found..!!\n");fflush(stdout);
				}
			}
			else
            {
				printf(" DesignRevision Sequence Query Tag Not Found..!!\n");fflush(stdout);
		    }
			if(titemobj_results)
			{
				MEM_free(titemobj_results);
			}
		}
		fprintf(fpOutput_file,"\n ,,,, E N D - O F    R E P O R T ,,,,\n");fflush(fpOutput_file);
		fclose(fpOutput_file);
        write2xml(Report,"</DetailsRpt>\n");
        fclose(Report);		
		printf("\n All Part Written Successfully on the Output File....\n");fflush(stdout);
		
		printf("Current File To Original File Move Start..!!\n");fflush(stdout);
		char* ShellCommandLine = NULL;
	    ShellCommandLine = (char *) MEM_alloc(1000*sizeof(char ));
		tc_strcpy(ShellCommandLine,"/user/srk/ProcessFiles.sh");
		tc_strcat(ShellCommandLine," ");
		tc_strcat(ShellCommandLine,"TEST");
		tc_strcat(ShellCommandLine," ");
		tc_strcat(ShellCommandLine,"TEST");
		tc_strcat(ShellCommandLine," ");
		tc_strcat(ShellCommandLine,"TEST");
		tc_strcat(ShellCommandLine," ");
		tc_strcat(ShellCommandLine,"TEST");
		tc_strcat(ShellCommandLine," ");
		tc_strcat(ShellCommandLine,PreVCompFile);
		system(ShellCommandLine);
		printf("Current File To Original File Move End..!!\n");fflush(stdout);
		
		char* RptShellCommandLine = NULL;
		RptShellCommandLine = (char *) MEM_alloc(1000*sizeof(char ));		
		printf("\n Email Shell Call Started...");fflush(stdout);
		tc_strcpy(RptShellCommandLine,"/user/srk/SendEmail.sh");
		tc_strcat(RptShellCommandLine," ");
		tc_strcat(RptShellCommandLine,RptFile);
		tc_strcat(RptShellCommandLine," ");
		tc_strcat(RptShellCommandLine,inp_email_strDup);
		printf("\n CommandLine: -------> [%s]",RptShellCommandLine);fflush(stdout);
		system(RptShellCommandLine); 
		printf("\n Email Shell Call Ended...");
	}
	else 
	{
		printf("\n Input_File is NULL..!!\n");fflush(stdout);
	}
	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");fflush(stdout);
	
    CLEANUP:
	ITK_exit_module(TRUE);	
	return ITK_ok;
}
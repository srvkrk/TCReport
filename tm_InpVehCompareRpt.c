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

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int TC_DSSet(char *FDSName, char *VSFile)
{	
	trimwhitespace(FDSName);
	tag_t tDSNQryobj = NULLTAG;
	int nds_entries = 1;
	int ds_Qryobj_found = 0;
	tag_t* tdsQryobj_results = NULLTAG;
	int u = 0;
	char temp[10000];
	char *VID_Str = NULL;
	char *VR_Str = NULL;
	char *VS_Str = NULL;
	char *VDes_Str = NULL;
	char *VPlat_Str = NULL;
	char *VDr_Str = NULL;
	char *VC_Str = NULL;
	char *VDT_Str = NULL;
	char *STData = (char *) malloc(500*sizeof(char));
	FILE *fpres_List = NULL;
	int iFail = ITK_ok;
	tag_t PropName_AttrID = NULLTAG;
	
	printf("\n Searched Dataset Name: [%s]\n", FDSName);fflush(stdout);
	printf("\n Searched File Name with Location: [%s]\n", VSFile);fflush(stdout);
    ITK_CALL(QRY_find2("Dataset Name",&tDSNQryobj));
    if(tDSNQryobj!=NULLTAG)
	{
		printf("\n Dataset Name Query Found Successfully..!!");fflush(stdout);
		char *DSEntries[1]  = {"Dataset Name"};
		char *DSValues[1]  = {FDSName};
		ITK_CALL(QRY_execute(tDSNQryobj, nds_entries, DSEntries, DSValues, &ds_Qryobj_found, &tdsQryobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Dataset Name Found: [%d]\n",ds_Qryobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(ds_Qryobj_found > 0)
		{
			printf(" Quiried Design Revision Found..!!\n");fflush(stdout);
			for (u = 0; u < ds_Qryobj_found; u++)
			{
				tag_t rev_tags_found = NULLTAG;
				rev_tags_found = tdsQryobj_results[u];
				if(rev_tags_found != NULLTAG)
				{	
			        fpres_List = fopen(VSFile,"r");
					if(fpres_List != NULL)
					{	
						printf("\n Output Response File Not Null Moving Forward..!!");fflush(stdout);
						while(fgets(temp, 10000, fpres_List)!= NULL)
						{
							VID_Str=strtok(temp,"^");
							VR_Str=strtok(NULL,"^");
							VS_Str=strtok(NULL,"^");
							VDes_Str=strtok(NULL,"^");
							VPlat_Str=strtok(NULL,"^");
							VDr_Str=strtok(NULL,"^");
							VC_Str=strtok(NULL,"^");
							VDT_Str=strtok(NULL,"^");
							
							tc_strcpy(STData,VID_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VR_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VS_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VDes_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VPlat_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VDr_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VC_Str);
							tc_strcat(STData,",");
							tc_strcat(STData,VDT_Str);
							tc_strcat(STData,",");
							trimwhitespace(STData);
							printf("\n Response Data1: [%s]", STData);fflush(stdout);
						}
						fclose(fpres_List) ;           
				        printf("\n All Output data Read Successfully From The File..!!\n");fflush(stdout);
					}
					printf("\n Response Data2: [%s]", STData);fflush(stdout);
					printf("\n Output Data Stamp Start..!!\n");fflush(stdout);
					printf("\n ~~~~~~~~ U P D A T I O N   S T A R T ~~~~~~~~\n");fflush(stdout);  
					ITK_CALL(AOM_refresh(tdsQryobj_results[u], POM_modify_lock));
					printf("\n Lock..!!\n");
					ITK_CALL(POM_attr_id_of_attr("object_desc", "Dataset", &PropName_AttrID));
					printf("\n Property Name Tag Found..!!\n");
					//ITK_CALL(POM_set_attr_string(1, &titemobj_results[i], PropName_AttrID, item_propvalue_strDup));
					//item_propvalue_strDupInt = atoi(item_propvalue_strDup);
					//ITK_CALL(POM_set_attr_string(1, &tdsQryobj_results[u], PropName_AttrID, "51530535R,B,2,712 LPT DCR35HSD 125B6M5 TT,ILMCV_LPT,DR3,0.000000,17_Jul_2024_18_04_01,"));
					ITK_CALL(POM_set_attr_string(1, &tdsQryobj_results[u], PropName_AttrID, STData));
					printf("\n Set Property Value..!!\n");
					ITK_CALL(POM_save_instances(1, &tdsQryobj_results[u], true));
					printf("\n Save...!!\n");
					ITK_CALL(AOM_refresh(tdsQryobj_results[u], POM_no_lock));
					printf("\n Unlock..!!\n");
					printf("\n ~~~~~~~~ U P D A T I O N   E N D ~~~~~~~~\n");fflush(stdout);
					printf("\n Output Data Stamp End..!!\n");fflush(stdout);
				}
				else
				{
					printf("\n Revision Tag Not Found..!!");fflush(stdout);
				}
			}
		}
		else
		{
			printf("\n Entered Dataset Name Not Found..!!");fflush(stdout);
		}	
	}
	else
	{
		printf("\n Dataset Name Tag Not Found..!!");fflush(stdout);
	}
	
	return iFail;	
}

char* TC_LibraryStatus(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* SubModStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup("Yes",&SubModStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("No",&SubModStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("No",&SubModStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("No",&SubModStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModStatus;
}

char* TC_LibraryRevStatus(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* SubModRevStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup(Tbl_SubModRev,&SubModRevStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("NA",&SubModRevStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("NA",&SubModRevStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("NA",&SubModRevStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModRevStatus;
}

char* TC_LibrarySeqStatus(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* SubModSeqStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup(Tbl_SubModSeq,&SubModSeqStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("NA",&SubModSeqStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("NA",&SubModSeqStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("NA",&SubModSeqStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModSeqStatus;
}

char* TC_LibraryGateStatus(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* Tbl_SubModDrAr = NULL;
	char* SubModDrArStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_drarstatus", &Tbl_SubModDrAr));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					printf("\n Table SubModule AR/DR: [%s]",Tbl_SubModDrAr);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					if(Tbl_SubModDrAr!=NULL)trimwhitespace(Tbl_SubModDrAr);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup(Tbl_SubModDrAr,&SubModDrArStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("NA",&SubModDrArStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("NA",&SubModDrArStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("NA",&SubModDrArStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModDrArStatus;
}

char* TC_LibraryMaxGateStatus(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* Tbl_SubModDrAr = NULL;
	char* Tbl_SubModMaxDrAr = NULL;
	char* SubModMaxDrArStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_drarstatus", &Tbl_SubModDrAr));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_info3", &Tbl_SubModMaxDrAr));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					printf("\n Table SubModule AR/DR: [%s]",Tbl_SubModDrAr);fflush(stdout);
					printf("\n Table SubModule Max AR/DR: [%s]",Tbl_SubModMaxDrAr);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					if(Tbl_SubModDrAr!=NULL)trimwhitespace(Tbl_SubModDrAr);
					if(Tbl_SubModMaxDrAr!=NULL)trimwhitespace(Tbl_SubModMaxDrAr);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup(Tbl_SubModMaxDrAr,&SubModMaxDrArStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("NA",&SubModMaxDrArStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("NA",&SubModMaxDrArStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("NA",&SubModMaxDrArStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModMaxDrArStatus;
}

char* TC_LibraryVehLinkFreq(char* SAddr, char* SNo, char* SRev, char* SSeq)
{
	trimwhitespace(SAddr);
	trimwhitespace(SNo);
	trimwhitespace(SRev);
	trimwhitespace(SSeq);
	tag_t tItemobj = NULLTAG;
	int n_entries = 1;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	tag_t tsubmodlib_rev = NULLTAG;
    int n_valid_rows=0;
	tag_t* valid_rowsTag = NULLTAG;
    int iValCnt = 0;
    char* Tbl_SubModNo = NULL;
	char* Tbl_SubModRev = NULL;
	char* Tbl_SubModSeq = NULL;
	char* Tbl_SubModDrAr = NULL;
	char* Tbl_SubModVehLink = NULL;
	char* SubModVehLinkFreqStatus = NULL;
	
	ITK_CALL(QRY_find2("SubModuleLibraryDetails",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query[SubModuleLibraryDetails] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[1]  = {"ID"};
		char *cValues[1]  = {SAddr};
		//char *cValues[1]  = {"A1A01"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Objects[SubModuleLibraryDetails] Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf("\n SubModule Address Revision Exist So Continue To Check Submodule Present or Not..!!\n");fflush(stdout);
			tsubmodlib_rev = titemobj_results[0];
			ITK_CALL(AOM_ask_table_rows(tsubmodlib_rev,"t5_Submoduledetail", &n_valid_rows,&valid_rowsTag));
			printf("\n No of Table Row: [%d]  For SubModule Address:  [%s]\n", n_valid_rows, SAddr);fflush(stdout);
			if(n_valid_rows>0)
			{
				for(iValCnt=0;iValCnt<n_valid_rows;iValCnt++)
				{
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_submoduleno", &Tbl_SubModNo));	
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_rev", &Tbl_SubModRev));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_seq", &Tbl_SubModSeq));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_drarstatus", &Tbl_SubModDrAr));
					ITK_CALL(AOM_ask_value_string(valid_rowsTag[iValCnt], "t5_info1", &Tbl_SubModVehLink));
					printf("\n Table SubModule No: [%s]",Tbl_SubModNo);fflush(stdout);
					printf("\n Table SubModule Rev: [%s]",Tbl_SubModRev);fflush(stdout);
					printf("\n Table SubModule Seq: [%s]",Tbl_SubModSeq);fflush(stdout);
					printf("\n Table SubModule AR/DR: [%s]",Tbl_SubModDrAr);fflush(stdout);
					printf("\n Table SubModule Vehicle Link Frequency: [%s]",Tbl_SubModVehLink);fflush(stdout);
					if(Tbl_SubModNo!=NULL)trimwhitespace(Tbl_SubModNo);
					if(Tbl_SubModRev!=NULL)trimwhitespace(Tbl_SubModRev);
					if(Tbl_SubModSeq!=NULL)trimwhitespace(Tbl_SubModSeq);
					if(Tbl_SubModDrAr!=NULL)trimwhitespace(Tbl_SubModDrAr);
					if(Tbl_SubModVehLink!=NULL)trimwhitespace(Tbl_SubModVehLink);
					//if((tc_strcmp(SNo,Tbl_SubModNo)==0) && (tc_strcmp(SRev,Tbl_SubModRev)==0) && (tc_strcmp(SSeq,Tbl_SubModSeq)==0))
					if(tc_strcmp(SNo,Tbl_SubModNo)==0)
					{
						printf("\n Input SubModule No And Table SubModule No Matched So Exit..!!\n");fflush(stdout);
						tc_strdup(Tbl_SubModVehLink,&SubModVehLinkFreqStatus);
                        goto jump;						
					}
					else
					{
						printf("\n Input SubModule No And Table SubModule Not Matched..!!\n");fflush(stdout);
					}
				}
			}
			else
			{
				printf("\n No Table Row Found For Input SubModule Address: [%s], SAddr\n");fflush(stdout);
				tc_strdup("NA",&SubModVehLinkFreqStatus);
			}    
		}
		else
		{
		   printf("\n SubModule Library Not Found..!!\n");fflush(stdout);
		   tc_strdup("NA",&SubModVehLinkFreqStatus);
		}					
	}
	else
	{
		printf(" Query[SubModuleLibraryDetails] Tag Not Found..!!");fflush(stdout);
		tc_strdup("NA",&SubModVehLinkFreqStatus);
	}
	
	jump:
	   printf("\n Input SubModule No And Table SubModule No Matched..!!\n");fflush(stdout);
	   
	return SubModVehLinkFreqStatus;
}

char* TC_PartDesc(char* PSrch,char* PRevSeqSrch)
{
	
	trimwhitespace(PSrch);
	trimwhitespace(PRevSeqSrch);
	tag_t tpQryobj = NULLTAG;
	int np_entries = 2;
	int np_Qryobj_found = 0;
	tag_t* tpQryobj_results = NULLTAG;
	char* cItem_Desc = NULL;
	char* cItem_DescDup = NULL;
	tag_t DesRev_tag = NULLTAG;
	char *Item_revseq = NULL;
	int m = 0;
	printf("\n Searched Part Number Value: [%s]\n", PSrch);fflush(stdout);
	printf("\n Searched Part Revision & Sequence Value: [%s]\n", PRevSeqSrch);fflush(stdout);
    ITK_CALL(QRY_find2("DesignRevision Sequence",&tpQryobj));
    if(tpQryobj!=NULLTAG)
	{
		printf("\n DesignRevision Sequence Query Found Successfully...\n");fflush(stdout);
		char *PartEntries[2]  = {"Revision","ID"};
		char *PartValues[2]  = {PRevSeqSrch,PSrch};
		ITK_CALL(QRY_execute(tpQryobj, np_entries, PartEntries, PartValues, &np_Qryobj_found, &tpQryobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n No of Revision Found: [%d]\n",np_Qryobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(np_Qryobj_found > 0)
		{
			printf(" Quiried Design Revision Found..!!\n");fflush(stdout);
			for (m = 0; m < np_Qryobj_found; m++)
			{
				tag_t rev_tags_found = NULLTAG;
				rev_tags_found = tpQryobj_results[m];
				if(rev_tags_found != NULLTAG)
				{	
					AOM_ask_value_string(tpQryobj_results[m],"object_desc",&cItem_Desc);
					printf("\n Item Description Before Dup & Trim:  <%s> \n",cItem_Desc);fflush(stdout);
					if(tc_strlen(cItem_Desc)>0)
					{
						tc_strdup(cItem_Desc,&cItem_DescDup);
					}
					else
					{
						tc_strdup("--",&cItem_DescDup);
						printf("\n Item Description Value is NULL");fflush(stdout);
					}
					trimwhitespace(cItem_DescDup);
					printf("\n Item Description Value After Dup & Trim: [%s]", cItem_DescDup);fflush(stdout);
					STRNG_replace_str(cItem_DescDup,","," ",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,";"," ",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,"\n"," ",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,"'"," ",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,"&","&amp;",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,"<","&lt;",&cItem_DescDup);
					STRNG_replace_str(cItem_DescDup,">","&gt;",&cItem_DescDup);
					printf("\n Item Description Final Value: [%s]", cItem_DescDup);fflush(stdout);
				}
				else
				{
					tc_strdup("--",&cItem_DescDup);
					printf("\nSorry! Revision Tag Not Found...");fflush(stdout);
				}
			}
		}
		else
		{
			tc_strdup("--",&cItem_DescDup);
			printf("\nSorry! Entered Revision Not Found...");fflush(stdout);
		}
		
	}
	else
	{
		tc_strdup("--",&cItem_DescDup);
		printf("\nSorry! DesignRevision Sequence Query Tag Not Found...");fflush(stdout);
	}
	
	return cItem_DescDup;	
}

int bom_sub_child(tag_t* tBOM_Sub_Children, int iSubSubNumber_Child, char* VNo, char* VRev, char* VSeq, char* MainDesc, char* MainDrAr, char* VRpt, FILE* FP_VComRpt, char* VFResData, char* VFSide)
{
		char* cItem_Id = NULL;
		char* cItem_RevSeq = NULL;
		char* cItem_Rev = NULL;
		char* cItem_Seq = NULL;
		char* cItem_Desc = NULL;
		char* cModAddress = NULL;
		char* cProdLine = NULL;
		char* cProdLineDup = NULL;
		char* cPlatform = NULL;
		char* cPlatformDup = NULL;
		char* cProjCode = NULL;
	    char* cProjCodeDup = NULL;
	    char* cDesGrp = NULL;
	    char* cDesGrpDup = NULL;
		char* cArDrStatus = NULL;
		char* cArDrStatusDup = NULL;
		char* cPartType = NULL;
		char* cPartTypeDup = NULL;
		char* cQuantity = NULL;
		char* cQuantityDup = NULL;
	    tag_t PrtMstrTag = NULLTAG;
	    char *MstrUOMTag = NULL;
	    char *MstrUOMTagDup = NULL;
		int j =0;
		int iFail = ITK_ok;
		int iNumber_SubChild = 0;
		tag_t tChild = NULLTAG;
		tag_t* tSubChild = NULLTAG;
		char* LibStatus = NULL;
		char* LibRevStatus = NULL;
		char* LibSeqStatus = NULL;
		char* LibGateStatus = NULL;
		char* LibMaxGateStatus = NULL;
		char* LibVehLinkFreqStatus = NULL;
		int yescount = 0;
		int nocount = 0;
		int maxdrpasscount = 0;
		int maxdrfailcount = 0;
		int compliance = 0;
		int totalcount = 0;
		double finalcompliance;
		char total[10];
		char totalpresent[10];
		char totalnotpresent[10];
		char complianceper[10];
		char maxdrpasscountdup[10];
		char maxdrfailcountdup[10];
		int maxcompliance = 0;
		int allcompliance = 0;
		double maxdrfinalcompliance;
		double alldrfinalcompliance;
		char* totalpresentDup = NULL;
		char* totalnotpresentDup = NULL;
		char* maxdrpasscountdupfinal = NULL;
		char* maxdrfailcountdupfinal = NULL;
		char *PreVCompFile = (char *) malloc(100*sizeof(char));
		char finalslno[10];
		char DTStamp[100] = "";
		time_t 	dtnow;
		struct 	tm dtwhen;
		time(&dtnow);
		dtwhen = *localtime(&dtnow);
		strftime(DTStamp,100,"%d_%b_%Y_%H_%M_%S",&dtwhen);
		printf(" Current TimeStamp: [%s]\n", DTStamp);fflush(stdout);
		
		for(j = 0; j < iSubSubNumber_Child; j++)
		{	
	
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_item_item_id", &cItem_Id));
			trimwhitespace(cItem_Id);
			printf("\n Part No Value After Trim: [%s]\n", cItem_Id);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_rev_item_revision_id", &cItem_RevSeq));
			trimwhitespace(cItem_RevSeq);
			printf("\n Part Rev-Seq Value After Trim: [%s]\n", cItem_RevSeq);fflush(stdout);
			
			cItem_Desc = TC_PartDesc(cItem_Id,cItem_RevSeq);
			printf("\n Part Description Value: [%s]", cItem_Desc);fflush(stdout);
			
			cItem_Rev=strtok(cItem_RevSeq,";");
			cItem_Seq=strtok(NULL,";");
			printf("\n Part Rev Value After Token: [%s]\n", cItem_Rev);fflush(stdout);
			printf("\n Part Seq Value After Token: [%s]\n", cItem_Seq);fflush(stdout);
			
			cModAddress = subString(cItem_Id, 4, 5);
			trimwhitespace(cModAddress);
			printf("\n Part Module Address Value: [%s]", cModAddress);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_Platform", &cProdLine));
			if(tc_strlen(cProdLine)>0)
			{
				tc_strdup(cProdLine,&cProdLineDup);
			}
			else
			{
				tc_strdup("--",&cProdLineDup);
				printf("\n Product Line Value is NULL");fflush(stdout);
			}
			trimwhitespace(cProdLineDup);
			printf("\n Product Line Value After Dup & Trim: [%s]\n", cProdLineDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_Platform", &cPlatform));
			if(tc_strlen(cPlatform)>0)
			{
				tc_strdup(cPlatform,&cPlatformDup);
			}
			else
			{
				tc_strdup("--",&cPlatformDup);
				printf("\n Platform Value is NULL");fflush(stdout);
			}
			trimwhitespace(cPlatformDup);
			printf("\n Platform Value After Dup & Trim: [%s]\n", cPlatformDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_ProjectCode", &cProjCode));
			if(tc_strlen(cProjCode)>0)
			{
				tc_strdup(cProjCode,&cProjCodeDup);
			}
			else
			{
				tc_strdup("--",&cProjCodeDup);
				printf("\n Project Code Value is NULL");fflush(stdout);
			}
			trimwhitespace(cProjCodeDup);
			printf("\n Project Code Value After Dup & Trim: [%s]\n", cProjCodeDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_DesignGrp", &cDesGrp));
			if(tc_strlen(cDesGrp)>0)
			{
				tc_strdup(cDesGrp,&cDesGrpDup);
			}
			else
			{
				tc_strdup("--",&cDesGrpDup);
				printf("\n Design Group Value is NULL");fflush(stdout);
			}
			trimwhitespace(cDesGrpDup);
			printf("\n Design Group Value After Dup & Trim: [%s]\n", cDesGrpDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_PartStatus", &cArDrStatus));
			if(tc_strlen(cArDrStatus)>0)
			{
				tc_strdup(cArDrStatus,&cArDrStatusDup);
			}
			else
			{
				tc_strdup("--",&cArDrStatusDup);
				printf("\n Part AR/DR Status Value is NULL");fflush(stdout);
			}
			trimwhitespace(cArDrStatusDup);
			printf("\n Part AR/DR Status Value After Dup & Trim: [%s]\n", cArDrStatusDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_Design Revision_t5_PartType", &cPartType));
			if(tc_strlen(cPartType)>0)
			{
				tc_strdup(cPartType,&cPartTypeDup);
			}
			else
			{
				tc_strdup("--",&cPartTypeDup);
				printf("\n Part Type Value is NULL");fflush(stdout);
			}
			trimwhitespace(cPartTypeDup);
			printf("\n Part Type Value After Dup & Trim: [%s]", cPartTypeDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(tBOM_Sub_Children[j], "bl_quantity", &cQuantity));
			if(tc_strlen(cQuantity)>0)
			{
				tc_strdup(cQuantity,&cQuantityDup);
			}
			else
			{
				tc_strdup("--",&cQuantityDup);
				printf("\n Part Quantity Value is NULL");fflush(stdout);
			}
			trimwhitespace(cQuantityDup);
			printf("\n Part Quantity Value After Dup & Trim: [%s]", cQuantityDup);fflush(stdout);
			
			ITK_CALL(ITEM_find_item(cItem_Id,&PrtMstrTag));
			if(PrtMstrTag != NULLTAG)
			{
			   ITK_CALL(AOM_UIF_ask_value(PrtMstrTag,"uom_tag",&MstrUOMTag));
			}
			if(MstrUOMTag!=NULL)
			{
				tc_strdup(MstrUOMTag,&MstrUOMTagDup);
			}
			else
			{
				tc_strdup("--",&MstrUOMTagDup);
				printf("\n Master Unit of Measure Tag[uom_tag] is NULL..!!\n");fflush(stdout);
			}
			printf("\n Master Unit of Measure Tag[uom_tag]: [%s]\n", MstrUOMTagDup);fflush(stdout);
			
			printf("\n----------- C H I L D    L E V E L    I T E M    D E T A I L S -------------");fflush(stdout);
			printf("\nChild_Level Part No: [%s]", cItem_Id);
			printf("\nChild_Level Part Revision: [%s]", cItem_Rev);
			printf("\nChild_Level Part Sequence: [%s]", cItem_Seq);
			printf("\nChild_Level Part Description: [%s]", cItem_Desc);
			printf("\nChild_Level Part Address: [%s]", cModAddress);
			printf("\nChild_Level Part Product Line: [%s]", cProdLineDup);
			printf("\nChild_Level Part Platform: [%s]", cPlatformDup);
			printf("\nChild_Level Project Code: [%s]", cProjCodeDup);
			printf("\nChild_Level Design Group: [%s]", cDesGrpDup);
			printf("\nChild_Level Part AR/DR Status: [%s]", cArDrStatusDup);
			printf("\nChild_Level Part Type: [%s]", cPartTypeDup);
			printf("\nChild_Level Part Quantity: [%s]", cQuantityDup);
			printf("\nChild_Level UOM Tag: [%s]", MstrUOMTagDup);
			printf("\n-------------------------------------------------------------------------\n");
			if(tc_strlen(cPartTypeDup)>0)
		    {
				if(tc_strcmp(cPartTypeDup,"Module")==0)
				{
					totalcount = totalcount + 1;
					printf("\n Function2: SubModule Library Status Find Start\n");fflush(stdout);
                    LibStatus = TC_LibraryStatus(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function2: SubModule Library Status Find End\n");fflush(stdout);
					printf("\n Function3: SubModule Library Rev Status Find Start\n");fflush(stdout);
                    LibRevStatus = TC_LibraryRevStatus(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function3: SubModule Library Rev Status Find End\n");fflush(stdout);
					printf("\n Function4: SubModule Library Seq Status Find Start\n");fflush(stdout);
                    LibSeqStatus = TC_LibrarySeqStatus(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function4: SubModule Library Seq Status Find End\n");fflush(stdout);
					printf("\n Function5: SubModule Library Gateway Status Find Start\n");fflush(stdout);
                    LibGateStatus = TC_LibraryGateStatus(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function5: SubModule Library Gateway Status Find End\n");fflush(stdout);
					printf("\n Function6: SubModule Library Max Gateway Status Find Start\n");fflush(stdout);
                    LibMaxGateStatus = TC_LibraryMaxGateStatus(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function6: SubModule Library Max Gateway Status Find End\n");fflush(stdout);
					printf("\n Function7: SubModule Library Vehicle Frequency Count Find Start\n");fflush(stdout);
                    LibVehLinkFreqStatus = TC_LibraryVehLinkFreq(cModAddress,cItem_Id,cItem_Rev,cItem_Seq);
					printf("\n Function7: SubModule Library Vehicle Frequency Count Find End\n");fflush(stdout);
					if(tc_strcmp(LibStatus,"Yes")==0)
					{
						yescount = yescount + 1;
						if((tc_strcmp(LibMaxGateStatus,"DR4")==0) || (tc_strcmp(LibMaxGateStatus,"AR4")==0) || (tc_strcmp(LibMaxGateStatus,"DR5")==0) || (tc_strcmp(LibMaxGateStatus,"AR5")==0))
						{
							maxdrpasscount = maxdrpasscount + 1;
						}
						else
						{
							maxdrfailcount = maxdrfailcount + 1;
						}
					}
					else
					{
						nocount = nocount + 1;
					}
				    fprintf(FP_VComRpt,"%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^\n",cItem_Id,cItem_Rev,cItem_Seq,cItem_Desc,cModAddress,cProdLineDup,cPlatformDup,cProjCodeDup,cDesGrpDup,cArDrStatusDup,cPartTypeDup,cQuantityDup,MstrUOMTagDup,LibStatus,LibVehLinkFreqStatus,LibMaxGateStatus,VFResData);fflush(FP_VComRpt);
					if(cItem_Desc != NULL)
					{
						STRNG_replace_str(cItem_Desc,"&","&amp;",&cItem_Desc);
						STRNG_replace_str(cItem_Desc,"<","&lt;",&cItem_Desc);
						STRNG_replace_str(cItem_Desc,">","&gt;",&cItem_Desc);
					}
				}
			}
			/* ITK_CALL(BOM_line_ask_all_child_lines(tBOM_Sub_Children[j], &iNumber_SubChild, &tSubChild));
			printf("\n No of Sub Children Found: [%d]\n",iNumber_SubChild);fflush(stdout);
			if(iNumber_SubChild > 0)
			{
				printf("\n!!!!!!!!!! I N N E R  C H I L D   P A R T S   F O U N D !!!!!!!!!!");fflush(stdout);
				bom_sub_child(tSubChild,iNumber_SubChild,VNo,VRev,VSeq,MainDesc,MainDrAr,VRpt,FP_VComRpt,VFResData)
			} */
		}
		compliance = (yescount * 100);
		maxcompliance = (maxdrpasscount * 100);
		//allcompliance = (maxdrfailcount * 100);
		finalcompliance = (double) compliance / totalcount;
		maxdrfinalcompliance = (double) maxcompliance / totalcount;
		alldrfinalcompliance = (double) compliance / totalcount;
		tostring(total, totalcount);
		tostring(totalpresent, yescount);
		tostring(totalnotpresent, nocount);
		tostring(maxdrpasscountdup, maxdrpasscount);
		tostring(maxdrfailcountdup, maxdrfailcount);
		if(tc_strlen(totalpresent)>0)
		{
			tc_strdup(totalpresent,&totalpresentDup);
		}
		else
		{
			tc_strdup("0",&totalpresentDup);
			printf("\n Total Present Value is NULL");fflush(stdout);
		}
		if(tc_strlen(totalnotpresent)>0)
		{
			tc_strdup(totalnotpresent,&totalnotpresentDup);
		}
		else
		{
			tc_strdup("0",&totalnotpresentDup);
			printf("\n Total Not Present Value is NULL");fflush(stdout);
		}
		if(tc_strlen(maxdrpasscountdup)>0)
		{
			tc_strdup(maxdrpasscountdup,&maxdrpasscountdupfinal);
		}
		else
		{
			tc_strdup("0",&maxdrpasscountdupfinal);
			printf("\n No of Max DR4 and Above Submodules is NULL");fflush(stdout);
		}
		if(tc_strlen(maxdrfailcountdup)>0)
		{
			tc_strdup(maxdrfailcountdup,&maxdrfailcountdupfinal);
		}
		else
		{
			tc_strdup("0",&maxdrfailcountdupfinal);
			printf("\n No of Below DR4 Submodules is NULL");fflush(stdout);
		}
		printf("\n############ R E P O R T ############\n");fflush(stdout);
		printf("Total: %s\n", total);fflush(stdout);
		printf("Total Present: %s\n", totalpresentDup);fflush(stdout);
		printf("Total Not Present: %s\n", totalnotpresentDup);fflush(stdout); 
		printf("Compliance in Double: %lf\n", finalcompliance);fflush(stdout);
		char sfinalcompliance[100]; 
		sprintf(sfinalcompliance, "%.2f", finalcompliance); 
		printf("Compliance in String: [%s]", sfinalcompliance);fflush(stdout);
		char smaxdrfinalcompliance[100];
		char salldrfinalcompliance[100]; 
		sprintf(smaxdrfinalcompliance, "%.2f", maxdrfinalcompliance);
		sprintf(salldrfinalcompliance, "%.2f", alldrfinalcompliance); 
		printf("DR4 and Above Compliance in String: [%s]", smaxdrfinalcompliance);fflush(stdout);
		printf("All DR Status Compliance in String: [%s]", salldrfinalcompliance);fflush(stdout);
		printf("\n############ R E P O R T ############\n");fflush(stdout);
		if(tc_strcmp(VFSide,"P")==0)
		{
			write2xml(Report,"<PreviousCompare>\n");
			write2xml(Report,"<PVehNo>"); if(tc_strlen(VNo)>0) write2xml(Report,VNo); else write2xml(Report,"NA"); write2xml(Report,"</PVehNo>\n");
			write2xml(Report,"<PVehRev>"); if(tc_strlen(VRev)>0) write2xml(Report,VRev); else write2xml(Report,"NA"); write2xml(Report,"</PVehRev>\n");
			write2xml(Report,"<PVehSeq>"); if(tc_strlen(VSeq)>0) write2xml(Report,VSeq); else write2xml(Report,"NA"); write2xml(Report,"</PVehSeq>\n");
			write2xml(Report,"<PVehDesc>"); if(tc_strlen(MainDesc)>0) write2xml(Report,MainDesc); else write2xml(Report,"NA"); write2xml(Report,"</PVehDesc>\n");
			write2xml(Report,"<PVehDrAr>"); if(tc_strlen(MainDrAr)>0) write2xml(Report,MainDrAr); else write2xml(Report,"NA"); write2xml(Report,"</PVehDrAr>\n");
			write2xml(Report,"<PRevRule>"); if(tc_strlen(VNo)>0) write2xml(Report,"ERC release and above"); else write2xml(Report,"NA"); write2xml(Report,"</PRevRule>\n");
			write2xml(Report,"<PClosureRule>"); if(tc_strlen(VNo)>0) write2xml(Report,"BOMViewClosureRuleERC"); else write2xml(Report,"NA"); write2xml(Report,"</PClosureRule>\n");
			write2xml(Report,"<PTotalMod>"); if(tc_strlen(total)>0) write2xml(Report,total); else write2xml(Report,"NA"); write2xml(Report,"</PTotalMod>\n");
			write2xml(Report,"<PPresentMod>"); if(tc_strlen(totalpresentDup)>0) write2xml(Report,totalpresentDup); else write2xml(Report,"NA"); write2xml(Report,"</PPresentMod>\n");
			write2xml(Report,"<PNotPresentMod>"); if(tc_strlen(totalnotpresentDup)>0) write2xml(Report,totalnotpresentDup); else write2xml(Report,"NA"); write2xml(Report,"</PNotPresentMod>\n");
			write2xml(Report,"<PAboveMod>"); if(tc_strlen(maxdrpasscountdupfinal)>0) write2xml(Report,maxdrpasscountdupfinal); else write2xml(Report,"NA"); write2xml(Report,"</PAboveMod>\n");
			write2xml(Report,"<PBelowMod>"); if(tc_strlen(maxdrfailcountdupfinal)>0) write2xml(Report,maxdrfailcountdupfinal); else write2xml(Report,"NA"); write2xml(Report,"</PBelowMod>\n");
			write2xml(Report,"<PMaxPercent>"); if(tc_strlen(smaxdrfinalcompliance)>0) write2xml(Report,smaxdrfinalcompliance); else write2xml(Report,"NA"); write2xml(Report,"</PMaxPercent>\n");
			write2xml(Report,"<PAllPercent>"); if(tc_strlen(salldrfinalcompliance)>0) write2xml(Report,salldrfinalcompliance); else write2xml(Report,"NA"); write2xml(Report,"</PAllPercent>\n");
			write2xml(Report,"<PTimeStamp>"); if(tc_strlen(VRpt)>0) write2xml(Report,VRpt); else write2xml(Report,"NA"); write2xml(Report,"</PTimeStamp>\n");
			write2xml(Report,"</PreviousCompare>\n");
		}
		if(tc_strcmp(VFSide,"L")==0)
		{
			write2xml(Report,"<LatestCompare>\n");
			write2xml(Report,"<LVehNo>"); if(tc_strlen(VNo)>0) write2xml(Report,VNo); else write2xml(Report,"NA"); write2xml(Report,"</LVehNo>\n");
			write2xml(Report,"<LVehRev>"); if(tc_strlen(VRev)>0) write2xml(Report,VRev); else write2xml(Report,"NA"); write2xml(Report,"</LVehRev>\n");
			write2xml(Report,"<LVehSeq>"); if(tc_strlen(VSeq)>0) write2xml(Report,VSeq); else write2xml(Report,"NA"); write2xml(Report,"</LVehSeq>\n");
			write2xml(Report,"<LVehDesc>"); if(tc_strlen(MainDesc)>0) write2xml(Report,MainDesc); else write2xml(Report,"NA"); write2xml(Report,"</LVehDesc>\n");
			write2xml(Report,"<LVehDrAr>"); if(tc_strlen(MainDrAr)>0) write2xml(Report,MainDrAr); else write2xml(Report,"NA"); write2xml(Report,"</LVehDrAr>\n");
			write2xml(Report,"<LRevRule>"); if(tc_strlen(VNo)>0) write2xml(Report,"ERC release and above"); else write2xml(Report,"NA"); write2xml(Report,"</LRevRule>\n");
			write2xml(Report,"<LClosureRule>"); if(tc_strlen(VNo)>0) write2xml(Report,"BOMViewClosureRuleERC"); else write2xml(Report,"NA"); write2xml(Report,"</LClosureRule>\n");
			write2xml(Report,"<LTotalMod>"); if(tc_strlen(total)>0) write2xml(Report,total); else write2xml(Report,"NA"); write2xml(Report,"</LTotalMod>\n");
			write2xml(Report,"<LPresentMod>"); if(tc_strlen(totalpresentDup)>0) write2xml(Report,totalpresentDup); else write2xml(Report,"NA"); write2xml(Report,"</LPresentMod>\n");
			write2xml(Report,"<LNotPresentMod>"); if(tc_strlen(totalnotpresentDup)>0) write2xml(Report,totalnotpresentDup); else write2xml(Report,"NA"); write2xml(Report,"</LNotPresentMod>\n");
			write2xml(Report,"<LAboveMod>"); if(tc_strlen(maxdrpasscountdupfinal)>0) write2xml(Report,maxdrpasscountdupfinal); else write2xml(Report,"NA"); write2xml(Report,"</LAboveMod>\n");
			write2xml(Report,"<LBelowMod>"); if(tc_strlen(maxdrfailcountdupfinal)>0) write2xml(Report,maxdrfailcountdupfinal); else write2xml(Report,"NA"); write2xml(Report,"</LBelowMod>\n");
			write2xml(Report,"<LMaxPercent>"); if(tc_strlen(smaxdrfinalcompliance)>0) write2xml(Report,smaxdrfinalcompliance); else write2xml(Report,"NA"); write2xml(Report,"</LMaxPercent>\n");
			write2xml(Report,"<LAllPercent>"); if(tc_strlen(salldrfinalcompliance)>0) write2xml(Report,salldrfinalcompliance); else write2xml(Report,"NA"); write2xml(Report,"</LAllPercent>\n");
			write2xml(Report,"<LTimeStamp>"); if(tc_strlen(VRpt)>0) write2xml(Report,VRpt); else write2xml(Report,"NA"); write2xml(Report,"</LTimeStamp>\n");
			write2xml(Report,"</LatestCompare>\n");
		}
		printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");fflush(stdout);
		printf("Present SubModule in Library: [%s]\n", totalpresentDup);fflush(stdout);
		printf("Not Present SubModule in Library: [%s]\n", totalnotpresentDup);fflush(stdout);
		printf("Total Submodules: [%s]\n", total);fflush(stdout);
		printf("No of MAX DR4 and Above Submodules: [%s]\n", maxdrpasscountdupfinal);fflush(stdout); 
		printf("No of Below DR4 Submodules: [%s]\n", maxdrfailcountdupfinal);fflush(stdout);
		printf("DR4 and Above Compliance Percentage: [%s]\n", smaxdrfinalcompliance);fflush(stdout);
		printf("ALL DR Status Compliance Percentage: [%s]\n", salldrfinalcompliance);fflush(stdout);
		printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");fflush(stdout);
		
	return iFail;
}

int TC_VehChild_Details(char* Vehicle,char* VehicleRev,char* VehicleSeq,char* VDesc,char* VDrAr,char* RptDate,char* VehicleRS,FILE* VehRpt,char* VFData,char* VSide)
{
	tag_t top_Sub_Child_bom_window = NULLTAG;
	tag_t topsubrule = NULLTAG;
	int subrulefound = 0;
	tag_t* subclosurerule = NULL;
	tag_t sub_close_tag = NULLTAG;
	char** subrulename = NULL;
    char** subrulevalue = NULL;
	tag_t t_top_Sub_Child = NULLTAG;
	int iFail = ITK_ok;
	int itopSubNumber_Child = 0;
	tag_t* ttop_BOM_Children = NULLTAG;
	char* ctopSubItem_Id = NULL;
	char* ctopSubItem_RevSeq = NULL;
	char* ctopSubItem_Desc = NULL;
	char* ctopSubItem_Rev = NULL;
	char* ctopSubItem_Seq = NULL;
	char* ctopSubModAddress = NULL;
	char* ctopSubProdLine = NULL;
	char* ctopSubProdLineDup = NULL;
	char* ctopSubPlatform = NULL;
	char* ctopSubPlatformDup = NULL;
	char* ctopSubProjCode = NULL;
	char* ctopSubProjCodeDup = NULL;
	char* ctopSubDesGrp = NULL;
	char* ctopSubDesGrpDup = NULL;
	char* ctopSubArDrStatus = NULL;
	char* ctopSubArDrStatusDup = NULL;
	char* ctopSubPartType = NULL;
	char* ctopSubPartTypeDup = NULL;
	char* ctopSubQuantity = NULL;
	char* ctopSubQuantityDup = NULL;
	tag_t PartMasterTag	= NULLTAG;
	char *MstrUnitTag = NULL;
	char *MstrUnitTagDup = NULL;
	
	PIE_scope_t scope;
    scope = PIE_TEAMCENTER;
	
	
	tag_t top_item = NULLTAG;
	ITK_CALL(ITEM_find_item(Vehicle, &top_item));
	printf("\n API[ITEM_find_item] Success..!!\n");fflush(stdout);
	tag_t topchildrev = NULLTAG;
	//ITK_CALL(ITEM_find_rev(top_child_item_id, child_item_revision_id, &Childrev));
	ITK_CALL(ITEM_find_revision(top_item, VehicleRS, &topchildrev));
	printf("\n API[ITEM_find_revision] Success..!!\n");fflush(stdout);
	if(topchildrev != NULLTAG)
    {	
		ITK_CALL(BOM_create_window(&top_Sub_Child_bom_window));
		printf("\n API[BOM_create_window] Success..!!\n");fflush(stdout);
		ITK_CALL(CFM_find("ERC release and above", &topsubrule));
		//ITK_CALL(CFM_find(RevRule, &topsubrule));
		printf("\n API[CFM_find] Revision Rule Success..!!\n");fflush(stdout);
		ITK_CALL(BOM_set_window_config_rule(top_Sub_Child_bom_window, topsubrule));
        printf("\n API[BOM_set_window_config_rule] Success..!!\n");fflush(stdout);		
		ITK_CALL(PIE_find_closure_rules2("BOMViewClosureRuleERC",PIE_TEAMCENTER, &subrulefound, &subclosurerule));
		printf("\n API[PIE_find_closure_rules2] Closure Rule Find Success..!!\n");fflush(stdout);
		printf("\n No of Rule Found: [%d]\n",subrulefound);fflush(stdout);
		if (subrulefound > 0)
		{
			sub_close_tag = subclosurerule[0];
		}
		ITK_CALL(BOM_window_set_closure_rule(top_Sub_Child_bom_window,sub_close_tag,0,subrulename,subrulevalue));
		printf("\n API[BOM_window_set_closure_rule] Closure Rule Set Success..!!\n");fflush(stdout);
		ITK_CALL(BOM_set_window_pack_all(top_Sub_Child_bom_window, TRUE));
		printf("\n API[BOM_set_window_pack_all] BOM Window Pack Success..!!\n");fflush(stdout);
		ITK_CALL(BOM_set_window_top_line(top_Sub_Child_bom_window, NULLTAG, topchildrev, NULLTAG, &t_top_Sub_Child));
		printf("\n API[BOM_set_window_top_line] Top Line Set Success..!!\n");fflush(stdout);
	    if(t_top_Sub_Child != NULLTAG)
        {
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_item_item_id", &ctopSubItem_Id));
			trimwhitespace(ctopSubItem_Id);
			printf("\n Part No Value After Trim: [%s]\n", ctopSubItem_Id);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_rev_item_revision_id", &ctopSubItem_RevSeq));
			trimwhitespace(ctopSubItem_RevSeq);
			printf("\n Part Rev-Seq Value After Trim: [%s]\n", ctopSubItem_RevSeq);fflush(stdout);
			
			ctopSubItem_Desc = TC_PartDesc(ctopSubItem_Id,ctopSubItem_RevSeq);
			printf("\n Part Description Value: [%s]", ctopSubItem_Desc);fflush(stdout);
			
			ctopSubItem_Rev=strtok(ctopSubItem_RevSeq,";");
			ctopSubItem_Seq=strtok(NULL,";");
			printf("\n Part Rev Value After Token: [%s]\n", ctopSubItem_Rev);fflush(stdout);
			printf("\n Part Seq Value After Token: [%s]\n", ctopSubItem_Seq);fflush(stdout);
			
			ctopSubModAddress = subString(ctopSubItem_Id, 4, 5);
			trimwhitespace(ctopSubModAddress);
			printf("\n Part Module Address Value: [%s]", ctopSubModAddress);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_Platform", &ctopSubProdLine));
			if(tc_strlen(ctopSubProdLine)>0)
			{
				tc_strdup(ctopSubProdLine,&ctopSubProdLineDup);
			}
			else
			{
				tc_strdup("--",&ctopSubProdLineDup);
				printf("\n Product Line Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubProdLineDup);
			printf("\n Product Line Value After Dup & Trim: [%s]\n", ctopSubProdLineDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_Platform", &ctopSubPlatform));
			if(tc_strlen(ctopSubPlatform)>0)
			{
				tc_strdup(ctopSubPlatform,&ctopSubPlatformDup);
			}
			else
			{
				tc_strdup("--",&ctopSubPlatformDup);
				printf("\n Platform Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubPlatformDup);
			printf("\n Platform Value After Dup & Trim: [%s]\n", ctopSubPlatformDup);fflush(stdout);
			
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_ProjectCode", &ctopSubProjCode));
			if(tc_strlen(ctopSubProjCode)>0)
			{
				tc_strdup(ctopSubProjCode,&ctopSubProjCodeDup);
			}
			else
			{
				tc_strdup("--",&ctopSubProjCodeDup);
				printf("\n Project Code Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubProjCodeDup);
			printf("\n Project Code Value After Dup & Trim: [%s]\n", ctopSubProjCodeDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_DesignGrp", &ctopSubDesGrp));
			if(tc_strlen(ctopSubDesGrp)>0)
			{
				tc_strdup(ctopSubDesGrp,&ctopSubDesGrpDup);
			}
			else
			{
				tc_strdup("--",&ctopSubDesGrpDup);
				printf("\n Design Group Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubDesGrpDup);
			printf("\n Design Group Value After Dup & Trim: [%s]\n", ctopSubDesGrpDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_PartStatus", &ctopSubArDrStatus));
			if(tc_strlen(ctopSubArDrStatus)>0)
			{
				tc_strdup(ctopSubArDrStatus,&ctopSubArDrStatusDup);
			}
			else
			{
				tc_strdup("--",&ctopSubArDrStatusDup);
				printf("\n Part AR/DR Status Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubArDrStatusDup);
			printf("\n Part AR/DR Status Value After Dup & Trim: [%s]\n", ctopSubArDrStatusDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_Design Revision_t5_PartType", &ctopSubPartType));
			if(tc_strlen(ctopSubPartType)>0)
			{
				tc_strdup(ctopSubPartType,&ctopSubPartTypeDup);
			}
			else
			{
				tc_strdup("--",&ctopSubPartTypeDup);
				printf("\n Part Type Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubPartTypeDup);
			printf("\n Part Type Value After Dup & Trim: [%s]", ctopSubPartTypeDup);fflush(stdout);
			
			ITK_CALL(AOM_UIF_ask_value(t_top_Sub_Child, "bl_quantity", &ctopSubQuantity));
			if(tc_strlen(ctopSubQuantity)>0)
			{
				tc_strdup(ctopSubQuantity,&ctopSubQuantityDup);
			}
			else
			{
				tc_strdup("--",&ctopSubQuantityDup);
				printf("\n Part Quantity Value is NULL");fflush(stdout);
			}
			trimwhitespace(ctopSubQuantityDup);
			printf("\n Part Quantity Value After Dup & Trim: [%s]", ctopSubQuantityDup);fflush(stdout);
			
			ITK_CALL(ITEM_find_item(ctopSubItem_Id,&PartMasterTag));
			if(PartMasterTag != NULLTAG)
			{
			   ITK_CALL(AOM_UIF_ask_value(PartMasterTag,"uom_tag",&MstrUnitTag));
			}
			if(MstrUnitTag!=NULL)
			{
				tc_strdup(MstrUnitTag,&MstrUnitTagDup);
			}
			else
			{
				tc_strdup("--",&MstrUnitTagDup);
				printf("\n Master Unit of Measure Tag[uom_tag] is NULL..!!\n");fflush(stdout);
			}
			printf("\n Master Unit of Measure Tag[uom_tag]: [%s]\n", MstrUnitTagDup);fflush(stdout);
			
			printf("\n----------- T O P    L E V E L    I T E M    D E T A I L S -------------");fflush(stdout);
			printf("\nTop_Level Part No: [%s]", ctopSubItem_Id);
			printf("\nTop_Level Rev: [%s]", ctopSubItem_Rev);
			printf("\nTop_Level Seq: [%s]", ctopSubItem_Seq);
			printf("\nTop_Level Description: [%s]", ctopSubItem_Desc);
			printf("\nTop_Level Module Address: [%s]", ctopSubModAddress);
			printf("\nTop_Level Product Line: [%s]", ctopSubProdLineDup);
			printf("\nTop_Level Platform: [%s]", ctopSubPlatformDup);
			printf("\nTop_Level Project Code: [%s]", ctopSubProjCodeDup);
			printf("\nTop_Level Design Group: [%s]", ctopSubDesGrpDup);
			printf("\nTop_Level AR/DR: [%s]", ctopSubArDrStatusDup);
			printf("\nTop_Level Part Type: [%s]", ctopSubPartTypeDup);
			printf("\nTop_Level QTY: [%s]", ctopSubQuantityDup);
			printf("\nTop_Level UOM Tag: [%s]", MstrUnitTagDup);		
			printf("\n-------------------------------------------------------------------------\n");
			if(tc_strlen(ctopSubPartTypeDup)>0)
		    {
				if(tc_strcmp(ctopSubPartTypeDup,"Module")==0)
				{
				   fprintf(VehRpt,"%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^%s^\n",ctopSubItem_Id,ctopSubItem_Rev,ctopSubItem_Seq,ctopSubItem_Desc,ctopSubModAddress,ctopSubProdLineDup,ctopSubPlatformDup,ctopSubProjCodeDup,ctopSubDesGrpDup,ctopSubArDrStatusDup,ctopSubPartTypeDup,ctopSubQuantityDup,MstrUnitTagDup,"NA","NA","NA",VFData);fflush(VehRpt);
				}
			}
			ITK_CALL(BOM_line_ask_all_child_lines(t_top_Sub_Child, &itopSubNumber_Child, &ttop_BOM_Children));
			printf("\n API[BOM_line_ask_all_child_lines] Child Find Success..!!\n");fflush(stdout);
			printf("\n No of Children Found: [%d]\n",itopSubNumber_Child);fflush(stdout);
			if(itopSubNumber_Child>0)
			{
				printf("\n!!!!!!!!! C H I L D   P A R T S   F O U N D !!!!!!!!!!");fflush(stdout);
				bom_sub_child(ttop_BOM_Children, itopSubNumber_Child, Vehicle, VehicleRev, VehicleSeq, VDesc, VDrAr, RptDate, VehRpt, VFData, VSide);
			}
        }
	    ITK_CALL(BOM_close_window(top_Sub_Child_bom_window));
	    printf("\n API[BOM_close_window] BOM Window Close Success..!!\n");fflush(stdout);
	}
	return iFail;	
}

int ITK_user_main(int argc,char* argv[]) 
{
	char *message;
	char *loggedInUser = NULL;
	tag_t tItemobj = NULLTAG;
	int n_entries = 2;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	int i = 0;
	int j = 0;
	tag_t DesRev_tag = NULLTAG;
	char *latest_item_id_str = NULL;
	char *latest_item_id_strDup = NULL;
	char *latest_item_revseq_str = NULL;
	char *latest_item_revseq_strDup = NULL;
	char *latest_Newitem_revseq_str = NULL;
	char *latest_Newitem_revseq_strDup = NULL;
	char *latest_item_rev_str = NULL;
	char *latest_item_rev_strDup = NULL;
	char *latest_item_seq_str = NULL;
	char *latest_item_seq_strDup = NULL;
	char *latest_item_drar_str = NULL;
	char *latest_item_drar_strDup = NULL;
	char *latest_Veh_Desc = NULL;
	char *latest_Veh_DescDup = NULL;
	char *inp_id_str = NULL;
	char *inp_email_str = NULL;
	char *inp_id_strDup = NULL;
	char *inp_email_strDup = NULL;
	tag_t previous_item_tag = NULLTAG;
	int previous_list_count = 0;
	tag_t* previous_rev_list = NULLTAG;
	char *previous_item_id_str = NULL;
	char *previous_item_revseq_str = NULL;
	char *previous_item_relstatus = NULL;
	char *previous_item_id_strDup = NULL;
	char *previous_item_revseq_strDup = NULL;
	char *previous_Veh_Desc = NULL;
	char *previous_Veh_DescDup = NULL;
	char *previous_Newitem_revseq_str = NULL;
	char *previous_Newitem_revseq_strDup = NULL;
	char *previous_item_rev_str = NULL;
	char *previous_item_rev_strDup = NULL;
	char *previous_item_seq_str = NULL;
	char *previous_item_seq_strDup = NULL;
	char *previous_item_drar_str = NULL;
	char *previous_item_drar_strDup = NULL;
	char *LatestVCompFile = (char *) malloc(100*sizeof(char));
	char *LVRSDR = (char *) malloc(50*sizeof(char));
	char *PreviousVCompFile = (char *) malloc(100*sizeof(char));
	char *PVRSDR = (char *) malloc(50*sizeof(char));
	char *PreVCompFile = (char *) malloc(100*sizeof(char));
	char Buffer1[MAX_LINE_LENGTH];
	char Buffer2[MAX_LINE_LENGTH];
	char Buffer3[MAX_LINE_LENGTH];
	char Buffer4[MAX_LINE_LENGTH];
	char *previous_check_revseq_str = NULL;
	char *previous_check_revseq_strDup = NULL;
	char *previous_check_item_rev = NULL;
	char *previous_check_item_seq = NULL;
	char *previous_check_item_revDup = NULL;
	char *previous_check_item_seqDup = NULL;
    
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
	
	inp_id_str = ITK_ask_cli_argument("-Veh=");
	//inp_email_str = ITK_ask_cli_argument("-Email=");
	
	trimwhitespace(inp_id_str);
	//trimwhitespace(inp_email_str);
	if(inp_id_str!=NULL)tc_strdup(inp_id_str,&inp_id_strDup);
	//if(inp_email_str!=NULL)tc_strdup(inp_email_str,&inp_email_strDup);
	
	printf(" [1]: Input Part No(inp_id_strDup): [%s]\n",inp_id_strDup);
	//printf(" [2]: Input User Email(inp_email_strDup): [%s]\n",inp_email_strDup);
	
	char GenDate[100] = "";
	time_t 	now;
	struct 	tm when;
	time(&now);
	when = *localtime(&now);
	strftime(GenDate,100,"%d_%b_%Y_%H_%M_%S",&when);
	printf(" Current TimeStamp: [%s]\n", GenDate);fflush(stdout);
	
	printf("\n Generating XML Report File Name..!!");fflush(stdout);
	tc_strcpy(PreVCompFile,"/tmp/");
	tc_strcat(PreVCompFile,"VehicleCompareReport");
	tc_strcat(PreVCompFile,"_");
	tc_strcat(PreVCompFile,GenDate);
	tc_strcat(PreVCompFile,".xml");
	//Report = fopen("/tmp/VehicleCompareReport.xml","w");
	printf("\n Vehicle Compare Report File Name: [%s]", PreVCompFile);fflush(stdout);
	
	Report = fopen(PreVCompFile,"w");
	if(Report == NULL)
	{
		printf("ERROR: Unable To Open XML File..!!\n");
		return -1;
	}
	else
	{
		printf("XML File Opened Successfully..!!\n");
	}
	write2xml(Report,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	write2xml(Report,"<VehCompare>\n");
	
	printf("\n Finding Query[Latest Released Design Revision for ERC]..!!\n");fflush(stdout);
    ITK_CALL(QRY_find2("Latest Released Design Revision for ERC",&tItemobj));
    if(tItemobj != NULLTAG)
	{
		printf("\n Query[Latest Released Design Revision for ERC] Found Successfully..!!\n");fflush(stdout);
		char *cEntries[2]  = {"Item ID","Part Type"};
		char *cValues[2]  = {inp_id_strDup,"V"};
		//char *cValues[2]  = {"55551233R","V"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n -----------------------------------------------\n");fflush(stdout);
		printf("\n  No of Revision Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n -----------------------------------------------\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			printf(" Latest Released Revision Found Start..!!\n");fflush(stdout);
			for(i = 0; i < n_itemobj_found; i++)
			{
				DesRev_tag = titemobj_results[i];
				ITK_CALL(AOM_ask_value_string(titemobj_results[i],"item_id",&latest_item_id_str));
			    if(tc_strlen(latest_item_id_str)>0)
				{
					tc_strdup(latest_item_id_str,&latest_item_id_strDup);
					trimwhitespace(latest_item_id_strDup);
				}
				else
			    {
					tc_strdup("--",&latest_item_id_strDup);
					printf("\n Latest Released Vehicle Number Value is NULL..!!\n");fflush(stdout);
				}
				ITK_CALL(AOM_ask_value_string(titemobj_results[i],"item_revision_id",&latest_item_revseq_str));
			    if(tc_strlen(latest_item_revseq_str)>0)
				{
					tc_strdup(latest_item_revseq_str,&latest_item_revseq_strDup);
					trimwhitespace(latest_item_revseq_strDup);
				}
				else
			    {
					tc_strdup("--",&latest_item_revseq_strDup);
					printf("\n Latest Released Vehicle Revision Sequence Value is NULL..!!\n");fflush(stdout);
				}
				
				latest_Veh_Desc = TC_PartDesc(latest_item_id_strDup,latest_item_revseq_strDup);
				if(tc_strlen(latest_Veh_Desc)>0)
				{
					tc_strdup(latest_Veh_Desc,&latest_Veh_DescDup);
					trimwhitespace(latest_Veh_DescDup);
				}
				else
			    {
					tc_strdup("--",&latest_Veh_DescDup);
					printf("\n Latest Released Vehicle Description Value is NULL..!!\n");fflush(stdout);
				}
				printf("\n Latest Released Vehicle Description Value: [%s]\n", latest_Veh_DescDup);fflush(stdout);
				
				ITK_CALL(AOM_ask_value_string(titemobj_results[i],"item_revision_id",&latest_Newitem_revseq_str));
			    if(tc_strlen(latest_Newitem_revseq_str)>0)
				{
					tc_strdup(latest_Newitem_revseq_str,&latest_Newitem_revseq_strDup);
					trimwhitespace(latest_Newitem_revseq_strDup);
					latest_item_rev_str=strtok(latest_Newitem_revseq_strDup,";");
			        latest_item_seq_str=strtok(NULL,";");
					if(latest_item_rev_str!=NULL)tc_strdup(latest_item_rev_str,&latest_item_rev_strDup);
			        if(latest_item_seq_str!=NULL)tc_strdup(latest_item_seq_str,&latest_item_seq_strDup);
					trimwhitespace(latest_item_rev_strDup);
					trimwhitespace(latest_item_seq_strDup);
				}
				else
			    {
					tc_strdup("--",&latest_Newitem_revseq_strDup);
					printf("\n [New] Latest Released Vehicle Revision Sequence Value is NULL..!!\n");fflush(stdout);
				}
				ITK_CALL(AOM_ask_value_string(titemobj_results[i],"t5_PartStatus",&latest_item_drar_str));
			    if(tc_strlen(latest_item_drar_str)>0)
				{
					tc_strdup(latest_item_drar_str,&latest_item_drar_strDup);
					trimwhitespace(latest_item_drar_strDup);
				}
				else
			    {
					tc_strdup("--",&latest_item_drar_strDup);
					printf("\n Latest Released Vehicle DR/AR Status Value is NULL..!!\n");fflush(stdout);
				}	
			}
			printf(" Latest Released Revision Found End..!!\n");fflush(stdout);
			
			printf(" Previous Released Revision Found Start..!!\n");fflush(stdout);
			if(tc_strstr(latest_item_revseq_strDup,"NR;")==NULL)	//If Latest Released Revision Not NR Then Process To Find Previous Revision
			{
				printf(" Previous Released Revision Not NR..!!\n");fflush(stdout);
				ITK_CALL(ITEM_find_item(inp_id_strDup, &previous_item_tag));
				ITK_CALL(ITEM_list_all_revs (previous_item_tag, &previous_list_count, &previous_rev_list));
				printf("\n previous_list_count: [%d]\n",previous_list_count);fflush(stdout);
				if(previous_list_count > 1)
				{
					for(j = previous_list_count-2; j >= 0; j--)
					{
						ITK_CALL(AOM_UIF_ask_value(previous_rev_list[j],"item_revision_id",&previous_check_revseq_str));
						if(tc_strlen(previous_check_revseq_str)>0)
						{
							tc_strdup(previous_check_revseq_str,&previous_check_revseq_strDup);
							trimwhitespace(previous_check_revseq_strDup);
							previous_check_item_rev=strtok(previous_check_revseq_strDup,";");
							previous_check_item_seq=strtok(NULL,";");
							if(previous_check_item_rev!=NULL)tc_strdup(previous_check_item_rev,&previous_check_item_revDup);
							if(previous_check_item_seq!=NULL)tc_strdup(previous_check_item_seq,&previous_check_item_seqDup);
							trimwhitespace(previous_check_item_revDup);
							trimwhitespace(previous_check_item_seqDup);
						}
						else
						{
							tc_strdup("--",&previous_check_revseq_strDup);
							printf("\n [Check] Previous Released Vehicle Revision Sequence Value is NULL..!!\n");fflush(stdout);
						}
						printf("\n [Check] Latest Revision: [%s]\n",latest_item_rev_strDup);fflush(stdout);
						printf("\n [Check] Previous Revision: [%s]\n",previous_check_item_revDup);fflush(stdout);
						printf("\n [Check] Previous Sequence: [%s]\n",previous_check_item_seqDup);fflush(stdout);
						ITK_CALL(AOM_UIF_ask_value(previous_rev_list[j], "release_status_list", &previous_item_relstatus));
						if(tc_strcmp(latest_item_rev_strDup,previous_check_item_revDup)!=0)
						{
							printf("\n Latest Item Revision ID and Previous Item Revision ID Not Same!!\n");fflush(stdout);
							if((tc_strstr(previous_item_relstatus,"ERC Released")!=NULL)||(tc_strstr(previous_item_relstatus,"T5_LcsErcRlzd")!=NULL))
							{
								printf("\n Previous Released Revision Found So, Break..!!\n");fflush(stdout);
								ITK_CALL(AOM_UIF_ask_value(previous_rev_list[j], "item_id", &previous_item_id_str));
								if(tc_strlen(previous_item_id_str)>0)
								{
									tc_strdup(previous_item_id_str,&previous_item_id_strDup);
									trimwhitespace(previous_item_id_strDup);
								}
								else
								{
									tc_strdup("--",&previous_item_id_strDup);
									printf("\n Previous Released Vehicle Number is NULL..!!\n");fflush(stdout);
								}
								ITK_CALL(AOM_UIF_ask_value(previous_rev_list[j], "item_revision_id", &previous_item_revseq_str));
								if(tc_strlen(previous_item_revseq_str)>0)
								{
									tc_strdup(previous_item_revseq_str,&previous_item_revseq_strDup);
									trimwhitespace(previous_item_revseq_strDup);
								}
								else
								{
									tc_strdup("--",&previous_item_revseq_strDup);
									printf("\n Previous Released Vehicle Revision Sequence is NULL..!!\n");fflush(stdout);
								}
								previous_Veh_Desc = TC_PartDesc(previous_item_id_str,previous_item_revseq_str);
								if(tc_strlen(previous_Veh_Desc)>0)
								{
									tc_strdup(previous_Veh_Desc,&previous_Veh_DescDup);
									trimwhitespace(previous_Veh_DescDup);
								}
								else
								{
									tc_strdup("--",&previous_Veh_DescDup);
									printf("\n Previous Released Vehicle Description Value is NULL..!!\n");fflush(stdout);
								}
								printf("\n Previous Released Vehicle Description Value: [%s]\n", previous_Veh_DescDup);fflush(stdout);
								ITK_CALL(AOM_UIF_ask_value(previous_rev_list[j],"item_revision_id",&previous_Newitem_revseq_str));
								if(tc_strlen(previous_Newitem_revseq_str)>0)
								{
									tc_strdup(previous_Newitem_revseq_str,&previous_Newitem_revseq_strDup);
									trimwhitespace(previous_Newitem_revseq_strDup);
									previous_item_rev_str=strtok(previous_Newitem_revseq_strDup,";");
									previous_item_seq_str=strtok(NULL,";");
									if(previous_item_rev_str!=NULL)tc_strdup(previous_item_rev_str,&previous_item_rev_strDup);
									if(previous_item_seq_str!=NULL)tc_strdup(previous_item_seq_str,&previous_item_seq_strDup);
									trimwhitespace(previous_item_rev_strDup);
									trimwhitespace(previous_item_seq_strDup);
								}
								else
								{
									tc_strdup("--",&previous_Newitem_revseq_strDup);
									printf("\n [New] Previous Released Vehicle Revision Sequence Value is NULL..!!\n");fflush(stdout);
								}
								ITK_CALL(AOM_ask_value_string(previous_rev_list[j],"t5_PartStatus",&previous_item_drar_str));
								if(tc_strlen(previous_item_drar_str)>0)
								{
									tc_strdup(previous_item_drar_str,&previous_item_drar_strDup);
									trimwhitespace(previous_item_drar_strDup);
								}
								else
								{
									tc_strdup("--",&previous_item_drar_strDup);
									printf("\n Previous Released Vehicle DR/AR Status Value is NULL..!!\n");fflush(stdout);
								}	
								break;
							}
							else
							{
								continue;
							}
						}
						else
						{
							printf("\n Latest Item Revision ID and Previous Item Revision ID Same. So, Continue!!\n");fflush(stdout);
							continue;
						}
					}
				}
			}
			else
			{
				printf(" Previous Released Revision NR..!!\n");fflush(stdout);
				tc_strdup("Not_Present",&previous_item_id_strDup);
				tc_strdup("Not_Present",&previous_item_revseq_strDup);
				tc_strdup("Not_Present",&previous_Veh_DescDup);
				tc_strdup("Not_Present",&previous_item_drar_strDup);
			}
			printf(" Previous Released Revision Found End..!!\n");fflush(stdout);
			printf("\n#######################################################################\n");fflush(stdout);
			printf("\n  Latest Released Vehicle Number: [%s]\n",latest_item_id_strDup);fflush(stdout);
			printf("\n  Latest Released Vehicle Revision & Sequence: [%s]\n",latest_item_revseq_strDup);fflush(stdout);
			printf("\n  Latest Released Vehicle Description: [%s]\n",latest_Veh_DescDup);fflush(stdout);
			printf("\n  Latest Released Vehicle DR & AR Value: [%s]\n",latest_item_drar_strDup);fflush(stdout);
			printf("\n  Previous Released Vehicle Number: [%s]\n",previous_item_id_strDup);fflush(stdout);
			printf("\n  Previous Released Vehicle Revision & Sequence: [%s]\n",previous_item_revseq_strDup);fflush(stdout);
			printf("\n  Previous Released Vehicle Description: [%s]\n",previous_Veh_DescDup);fflush(stdout);
			printf("\n  Previous Released Vehicle DR & AR Value: [%s]\n",previous_item_drar_strDup);fflush(stdout);
			printf("\n#######################################################################\n");fflush(stdout);
			if((tc_strlen(latest_item_id_strDup)>0) && (tc_strcmp(previous_item_id_strDup,"Not_Present")!=0))
			{
				printf(" Latest And Previous Item Revision Found..!!\n");fflush(stdout);
				
				printf("\n Generating Previous Vehicle Compare File Name..!!\n");fflush(stdout);
				tc_strcpy(PreviousVCompFile,"/tmp/");
				tc_strcat(PreviousVCompFile,"PreviousVehCompare");
				tc_strcat(PreviousVCompFile,"_");
				tc_strcat(PreviousVCompFile,previous_item_id_strDup);
				tc_strcat(PreviousVCompFile,"_");
				tc_strcat(PreviousVCompFile,previous_item_rev_strDup);
				tc_strcat(PreviousVCompFile,"_");
				tc_strcat(PreviousVCompFile,previous_item_seq_strDup);
				tc_strcat(PreviousVCompFile,"_");
				tc_strcat(PreviousVCompFile,previous_item_drar_strDup);
				tc_strcat(PreviousVCompFile,"_");
				tc_strcat(PreviousVCompFile,GenDate);
				tc_strcat(PreviousVCompFile,".txt");
				printf("\n Previous Vehicle Compare File Name: [%s]", PreviousVCompFile);fflush(stdout);
				printf("\n Previous Vehicle Compare File Name Generated..!!\n");fflush(stdout);
				printf("\n Generating Previous Vehicle String Name..!!\n");fflush(stdout);
				tc_strcpy(PVRSDR,previous_item_id_strDup);
				tc_strcat(PVRSDR,"-");
				tc_strcat(PVRSDR,previous_item_rev_strDup);
				tc_strcat(PVRSDR,"-");
				tc_strcat(PVRSDR,previous_item_seq_strDup);
				tc_strcat(PVRSDR,"-");
				tc_strcat(PVRSDR,previous_item_drar_strDup);
				printf("\n Previous Vehicle String Name: [%s]", PVRSDR);fflush(stdout);
				printf("\n Previous Vehicle String Name Generated..!!\n");fflush(stdout);
				FILE* fppreviousvcomp_file = fopen(PreviousVCompFile, "w");
				if(fppreviousvcomp_file == NULL)
				{
					printf("\n Unable to Open Previous Vehicle Compare File: --------> [%s]\n",PreviousVCompFile);fflush(stdout);
					return 0;
				}
				printf("\n Function1: Previous Vehicle Child Details Find Start\n");fflush(stdout);
				TC_VehChild_Details(previous_item_id_strDup,previous_item_rev_strDup,previous_item_seq_strDup,previous_Veh_DescDup,previous_item_drar_strDup,GenDate,previous_item_revseq_strDup,fppreviousvcomp_file,PVRSDR,"P");
			    printf("\n Function1: Previous Vehicle Child Details Find End\n");fflush(stdout);
				fclose(fppreviousvcomp_file);
				
				printf("\n Generating Latest Vehicle Compare File Name..!!\n");fflush(stdout);
				tc_strcpy(LatestVCompFile,"/tmp/");
				tc_strcat(LatestVCompFile,"LatestVehCompare");
				tc_strcat(LatestVCompFile,"_");
				tc_strcat(LatestVCompFile,latest_item_id_strDup);
				tc_strcat(LatestVCompFile,"_");
				tc_strcat(LatestVCompFile,latest_item_rev_strDup);
				tc_strcat(LatestVCompFile,"_");
				tc_strcat(LatestVCompFile,latest_item_seq_strDup);
				tc_strcat(LatestVCompFile,"_");
				tc_strcat(LatestVCompFile,latest_item_drar_strDup);
				tc_strcat(LatestVCompFile,"_");
				tc_strcat(LatestVCompFile,GenDate);
				tc_strcat(LatestVCompFile,".txt");
				printf("\n Latest Vehicle Compare File Name: [%s]", LatestVCompFile);fflush(stdout);
				printf("\n Latest Vehicle Compare File Name Generated..!!\n");fflush(stdout);
				printf("\n Generating Latest Vehicle String Name..!!\n");fflush(stdout);
				tc_strcpy(LVRSDR,latest_item_id_strDup);
				tc_strcat(LVRSDR,"-");
				tc_strcat(LVRSDR,latest_item_rev_strDup);
				tc_strcat(LVRSDR,"-");
				tc_strcat(LVRSDR,latest_item_seq_strDup);
				tc_strcat(LVRSDR,"-");
				tc_strcat(LVRSDR,latest_item_drar_strDup);
				printf("\n Latest Vehicle String Name: [%s]", LVRSDR);fflush(stdout);
				printf("\n Latest Vehicle String Name Generated..!!\n");fflush(stdout);
				FILE* fplatestvcomp_file = fopen(LatestVCompFile, "w");
				if(fplatestvcomp_file == NULL)
				{
					printf("\n Unable to Open Latest Vehicle Compare File: --------> [%s]\n",LatestVCompFile);fflush(stdout);
					return 0;
				}
				printf("\n Function2: Latest Vehicle Child Details Find Start\n");fflush(stdout);
				TC_VehChild_Details(latest_item_id_strDup,latest_item_rev_strDup,latest_item_seq_strDup,latest_Veh_DescDup,latest_item_drar_strDup,GenDate,latest_item_revseq_strDup,fplatestvcomp_file,LVRSDR,"L");
			    printf("\n Function2: Latest Vehicle Child Details Find End\n");fflush(stdout);
				fclose(fplatestvcomp_file);
				
				printf("\n File Compare [Latest with Previous] Start..!!\n");fflush(stdout);
	            char *LPMPart_no_Str1 = NULL;
				char *LPMPart_rev_Str1 = NULL;
				char *LPMPart_seq_Str1 = NULL;
				char *LPMPart_desc_Str1 = NULL;
				char *LPMPart_add_Str1 = NULL;
				char *LPMPart_prod_Str1 = NULL;
				char *LPMPart_plat_Str1 = NULL;
				char *LPMPart_proj_Str1 = NULL;
				char *LPMPart_des_Str1 = NULL;
				char *LPMPart_drar_Str1 = NULL;
				char *LPMPart_ptype_Str1 = NULL;
				char *LPMPart_pqty_Str1 = NULL;
				char *LPMPart_puom_Str1 = NULL;
				char *LPMPart_lib_Str1 = NULL;
				char *LPMPart_vehfreq_Str1 = NULL;
				char *LPMPart_vehmaxdrar_Str1 = NULL;
				char *LPMPart_psdata_Str1 = NULL;
				FILE *fp1LatestMaster_List = fopen(LatestVCompFile, "r");
				char *PartDataFile = (char *) malloc(50*sizeof(char));
                if(fp1LatestMaster_List != NULL)
				{
					printf("\n Master_File[Latest] Not Null..!!\n");fflush(stdout);
					while(fgets(Buffer1,MAX_LINE_LENGTH,fp1LatestMaster_List)!=NULL)
                    {
                        LPMPart_no_Str1=strtok(Buffer1,"^");
						LPMPart_rev_Str1=strtok(NULL,"^");
						LPMPart_seq_Str1=strtok(NULL,"^");
						LPMPart_desc_Str1=strtok(NULL,"^");
						LPMPart_add_Str1=strtok(NULL,"^");
						LPMPart_prod_Str1=strtok(NULL,"^");
						LPMPart_plat_Str1=strtok(NULL,"^");
						LPMPart_proj_Str1=strtok(NULL,"^");
						LPMPart_des_Str1=strtok(NULL,"^");
						LPMPart_drar_Str1=strtok(NULL,"^");
						LPMPart_ptype_Str1=strtok(NULL,"^");
						LPMPart_pqty_Str1=strtok(NULL,"^");
						LPMPart_puom_Str1=strtok(NULL,"^");
						LPMPart_lib_Str1=strtok(NULL,"^");
						LPMPart_vehfreq_Str1=strtok(NULL,"^");
						LPMPart_vehmaxdrar_Str1=strtok(NULL,"^");
						LPMPart_psdata_Str1=strtok(NULL,"^");
                        if(LPMPart_no_Str1!=NULL)trimwhitespace(LPMPart_no_Str1);
						if(LPMPart_rev_Str1!=NULL)trimwhitespace(LPMPart_rev_Str1);
						if(LPMPart_seq_Str1!=NULL)trimwhitespace(LPMPart_seq_Str1);
						if(LPMPart_desc_Str1!=NULL)trimwhitespace(LPMPart_desc_Str1);
						if(LPMPart_add_Str1!=NULL)trimwhitespace(LPMPart_add_Str1);
					    //if(LPMPart_prod_Str1!=NULL)trimwhitespace(LPMPart_prod_Str1);
					    //if(LPMPart_plat_Str1!=NULL)trimwhitespace(LPMPart_plat_Str1);
						if(LPMPart_prod_Str1 != NULL)
						{
							STRNG_replace_str(LPMPart_prod_Str1,"&","&amp;",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,"<","&lt;",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,">","&gt;",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,","," ",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,";"," ",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,"\n"," ",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,"'"," ",&LPMPart_prod_Str1);
							STRNG_replace_str(LPMPart_prod_Str1,"/"," ",&LPMPart_prod_Str1);
						}
						if(LPMPart_plat_Str1 != NULL)
						{
							STRNG_replace_str(LPMPart_plat_Str1,"&","&amp;",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,"<","&lt;",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,">","&gt;",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,","," ",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,";"," ",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,"\n"," ",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,"'"," ",&LPMPart_plat_Str1);
							STRNG_replace_str(LPMPart_plat_Str1,"/"," ",&LPMPart_plat_Str1);
						}
						if(LPMPart_proj_Str1!=NULL)trimwhitespace(LPMPart_proj_Str1);
						if(LPMPart_des_Str1!=NULL)trimwhitespace(LPMPart_des_Str1);
						if(LPMPart_drar_Str1!=NULL)trimwhitespace(LPMPart_drar_Str1);
						if(LPMPart_ptype_Str1!=NULL)trimwhitespace(LPMPart_ptype_Str1);
						if(LPMPart_pqty_Str1!=NULL)trimwhitespace(LPMPart_pqty_Str1);
						if(LPMPart_puom_Str1!=NULL)trimwhitespace(LPMPart_puom_Str1);
						if(LPMPart_lib_Str1!=NULL)trimwhitespace(LPMPart_lib_Str1);
						if(LPMPart_vehfreq_Str1!=NULL)trimwhitespace(LPMPart_vehfreq_Str1);
						if(LPMPart_vehmaxdrar_Str1!=NULL)trimwhitespace(LPMPart_vehmaxdrar_Str1);
						if(LPMPart_psdata_Str1!=NULL)trimwhitespace(LPMPart_psdata_Str1);
                       
					    char *LPMPart_no_Str2 = NULL;
						char *LPMPart_rev_Str2 = NULL;
						char *LPMPart_seq_Str2 = NULL;
						char *LPMPart_desc_Str2 = NULL;
						char *LPMPart_add_Str2 = NULL;
						char *LPMPart_prod_Str2 = NULL;
						char *LPMPart_plat_Str2 = NULL;
						char *LPMPart_proj_Str2 = NULL;
						char *LPMPart_des_Str2 = NULL;
						char *LPMPart_drar_Str2 = NULL;
						char *LPMPart_ptype_Str2 = NULL;
						char *LPMPart_pqty_Str2 = NULL;
						char *LPMPart_puom_Str2 = NULL;
						char *LPMPart_lib_Str2 = NULL;
						char *LPMPart_vehfreq_Str2 = NULL;
						char *LPMPart_vehmaxdrar_Str2 = NULL;
						char *LPMPart_psdata_Str2 = NULL;
						char* partstatus = NULL;
                        FILE *fp1PreviousMaster_List = fopen(PreviousVCompFile, "r");						
						if(fp1PreviousMaster_List != NULL)
						{
							printf("\n Child_File[Previous] Not Null..!!\n");fflush(stdout);
							while(fgets(Buffer2,MAX_LINE_LENGTH,fp1PreviousMaster_List)!=NULL)
							{
								LPMPart_no_Str2=strtok(Buffer2,"^");
								LPMPart_rev_Str2=strtok(NULL,"^");
								LPMPart_seq_Str2=strtok(NULL,"^");
								LPMPart_desc_Str2=strtok(NULL,"^");
								LPMPart_add_Str2=strtok(NULL,"^");
								LPMPart_prod_Str2=strtok(NULL,"^");
								LPMPart_plat_Str2=strtok(NULL,"^");
								LPMPart_proj_Str2=strtok(NULL,"^");
								LPMPart_des_Str2=strtok(NULL,"^");
								LPMPart_drar_Str2=strtok(NULL,"^");
								LPMPart_ptype_Str2=strtok(NULL,"^");
								LPMPart_pqty_Str2=strtok(NULL,"^");
								LPMPart_puom_Str2=strtok(NULL,"^");
								LPMPart_lib_Str2=strtok(NULL,"^");
								LPMPart_vehfreq_Str2=strtok(NULL,"^");
								LPMPart_vehmaxdrar_Str2=strtok(NULL,"^");
								LPMPart_psdata_Str2=strtok(NULL,"^");
								if(LPMPart_no_Str2!=NULL)trimwhitespace(LPMPart_no_Str2);
								if(LPMPart_rev_Str2!=NULL)trimwhitespace(LPMPart_rev_Str2);
								if(LPMPart_seq_Str2!=NULL)trimwhitespace(LPMPart_seq_Str2);
								if(LPMPart_desc_Str2!=NULL)trimwhitespace(LPMPart_desc_Str2);
								if(LPMPart_add_Str2!=NULL)trimwhitespace(LPMPart_add_Str2);
								//if(LPMPart_prod_Str2!=NULL)trimwhitespace(LPMPart_prod_Str2);
								//if(LPMPart_plat_Str2!=NULL)trimwhitespace(LPMPart_plat_Str2);
								if(LPMPart_prod_Str2 != NULL)
								{
									STRNG_replace_str(LPMPart_prod_Str2,"&","&amp;",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,"<","&lt;",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,">","&gt;",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,","," ",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,";"," ",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,"\n"," ",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,"'"," ",&LPMPart_prod_Str2);
									STRNG_replace_str(LPMPart_prod_Str2,"/"," ",&LPMPart_prod_Str2);
								}
								if(LPMPart_plat_Str2 != NULL)
								{
									STRNG_replace_str(LPMPart_plat_Str2,"&","&amp;",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,"<","&lt;",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,">","&gt;",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,","," ",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,";"," ",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,"\n"," ",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,"'"," ",&LPMPart_plat_Str2);
									STRNG_replace_str(LPMPart_plat_Str2,"/"," ",&LPMPart_plat_Str2);
								}
								if(LPMPart_proj_Str2!=NULL)trimwhitespace(LPMPart_proj_Str2);
								if(LPMPart_des_Str2!=NULL)trimwhitespace(LPMPart_des_Str2);
								if(LPMPart_drar_Str2!=NULL)trimwhitespace(LPMPart_drar_Str2);
								if(LPMPart_ptype_Str2!=NULL)trimwhitespace(LPMPart_ptype_Str2);
								if(LPMPart_pqty_Str2!=NULL)trimwhitespace(LPMPart_pqty_Str2);
								if(LPMPart_puom_Str2!=NULL)trimwhitespace(LPMPart_puom_Str2);
								if(LPMPart_lib_Str2!=NULL)trimwhitespace(LPMPart_lib_Str2);
								if(LPMPart_vehfreq_Str2!=NULL)trimwhitespace(LPMPart_vehfreq_Str2);
								if(LPMPart_vehmaxdrar_Str2!=NULL)trimwhitespace(LPMPart_vehmaxdrar_Str2);
								
								if(LPMPart_psdata_Str2!=NULL)trimwhitespace(LPMPart_psdata_Str2);
								if(tc_strcmp(LPMPart_no_Str1,LPMPart_no_Str2)==0)
								{
									if(tc_strcmp(LPMPart_pqty_Str1,LPMPart_pqty_Str2)==0)
									{
										tc_strcpy(PartDataFile,LPMPart_psdata_Str1);
										tc_strcat(PartDataFile," / ");
										tc_strcat(PartDataFile,LPMPart_psdata_Str2);
										tc_strdup("Same",&partstatus);
										goto jump1;
									}
									else
									{
										tc_strdup("Updated",&partstatus);
										goto jump1;
									}
								}
								else
								{
									continue;
								}
							}
						}
						else 
						{
							printf("\n Child_File[Previous] is NULL..!!\n");fflush(stdout);
						}
						fclose(fp1PreviousMaster_List);
						if(tc_strlen(partstatus)>0)
						{
							printf("\n Already Updated..!!\n");fflush(stdout);
						}
						else
						{
							tc_strcpy(PartDataFile,LPMPart_psdata_Str1);
							tc_strdup("Added",&partstatus);
							write2xml(Report,"<ChildDetails>\n");
							write2xml(Report,"<PartNo>"); if(tc_strlen(LPMPart_no_Str1)>0) write2xml(Report,LPMPart_no_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartNo>\n");
							write2xml(Report,"<PartRev>"); if(tc_strlen(LPMPart_rev_Str1)>0) write2xml(Report,LPMPart_rev_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartRev>\n");
							write2xml(Report,"<PartSeq>"); if(tc_strlen(LPMPart_seq_Str1)>0) write2xml(Report,LPMPart_seq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartSeq>\n");
							write2xml(Report,"<PartDesc>"); if(tc_strlen(LPMPart_desc_Str1)>0) write2xml(Report,LPMPart_desc_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesc>\n");
							write2xml(Report,"<PartAddr>"); if(tc_strlen(LPMPart_add_Str1)>0) write2xml(Report,LPMPart_add_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartAddr>\n");
							write2xml(Report,"<PartProd>"); if(tc_strlen(LPMPart_prod_Str1)>0) write2xml(Report,LPMPart_prod_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProd>\n");
							write2xml(Report,"<PartPlat>"); if(tc_strlen(LPMPart_plat_Str1)>0) write2xml(Report,LPMPart_plat_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartPlat>\n");
							write2xml(Report,"<PartProj>"); if(tc_strlen(LPMPart_proj_Str1)>0) write2xml(Report,LPMPart_proj_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProj>\n");
							write2xml(Report,"<PartDesGrp>"); if(tc_strlen(LPMPart_des_Str1)>0) write2xml(Report,LPMPart_des_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesGrp>\n");
							write2xml(Report,"<PartDrAr>"); if(tc_strlen(LPMPart_drar_Str1)>0) write2xml(Report,LPMPart_drar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDrAr>\n");
							write2xml(Report,"<PartType>"); if(tc_strlen(LPMPart_ptype_Str1)>0) write2xml(Report,LPMPart_ptype_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartType>\n");
							write2xml(Report,"<LatestPartQty>"); if(tc_strlen(LPMPart_pqty_Str1)>0) write2xml(Report,LPMPart_pqty_Str1); else write2xml(Report,"NA"); write2xml(Report,"</LatestPartQty>\n");
							write2xml(Report,"<PreviousPartQty>"); if(tc_strlen(LPMPart_pqty_Str2)>0) write2xml(Report,"0"); else write2xml(Report,"NA"); write2xml(Report,"</PreviousPartQty>\n");
							write2xml(Report,"<PartUOM>"); if(tc_strlen(LPMPart_puom_Str1)>0) write2xml(Report,LPMPart_puom_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartUOM>\n");
							write2xml(Report,"<PartInLib>"); if(tc_strlen(LPMPart_lib_Str1)>0) write2xml(Report,LPMPart_lib_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartInLib>\n");
							write2xml(Report,"<PartFreq>"); if(tc_strlen(LPMPart_vehfreq_Str1)>0) write2xml(Report,LPMPart_vehfreq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartFreq>\n");
							write2xml(Report,"<PartMaxDRAR>"); if(tc_strlen(LPMPart_vehmaxdrar_Str1)>0) write2xml(Report,LPMPart_vehmaxdrar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartMaxDRAR>\n");
							write2xml(Report,"<PartStatus>"); if(tc_strlen(partstatus)>0)write2xml(Report,partstatus); else write2xml(Report,"NA"); write2xml(Report,"</PartStatus>\n");
							write2xml(Report,"<PartData>"); if(tc_strlen(PartDataFile)>0) write2xml(Report,PartDataFile); else write2xml(Report,"NA"); write2xml(Report,"</PartData>\n");
							write2xml(Report,"</ChildDetails>\n");
						}
						
						jump1:
                            write2xml(Report,"<ChildDetails>\n");
							write2xml(Report,"<PartNo>"); if(tc_strlen(LPMPart_no_Str1)>0) write2xml(Report,LPMPart_no_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartNo>\n");
							write2xml(Report,"<PartRev>"); if(tc_strlen(LPMPart_rev_Str1)>0) write2xml(Report,LPMPart_rev_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartRev>\n");
							write2xml(Report,"<PartSeq>"); if(tc_strlen(LPMPart_seq_Str1)>0) write2xml(Report,LPMPart_seq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartSeq>\n");
							write2xml(Report,"<PartDesc>"); if(tc_strlen(LPMPart_desc_Str1)>0) write2xml(Report,LPMPart_desc_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesc>\n");
							write2xml(Report,"<PartAddr>"); if(tc_strlen(LPMPart_add_Str1)>0) write2xml(Report,LPMPart_add_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartAddr>\n");
							write2xml(Report,"<PartProd>"); if(tc_strlen(LPMPart_prod_Str1)>0) write2xml(Report,LPMPart_prod_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProd>\n");
							write2xml(Report,"<PartPlat>"); if(tc_strlen(LPMPart_plat_Str1)>0) write2xml(Report,LPMPart_plat_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartPlat>\n");
							write2xml(Report,"<PartProj>"); if(tc_strlen(LPMPart_proj_Str1)>0) write2xml(Report,LPMPart_proj_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProj>\n");
							write2xml(Report,"<PartDesGrp>"); if(tc_strlen(LPMPart_des_Str1)>0) write2xml(Report,LPMPart_des_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesGrp>\n");
							write2xml(Report,"<PartDrAr>"); if(tc_strlen(LPMPart_drar_Str1)>0) write2xml(Report,LPMPart_drar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDrAr>\n");
							write2xml(Report,"<PartType>"); if(tc_strlen(LPMPart_ptype_Str1)>0) write2xml(Report,LPMPart_ptype_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartType>\n");
							write2xml(Report,"<LatestPartQty>"); if(tc_strlen(LPMPart_pqty_Str1)>0) write2xml(Report,LPMPart_pqty_Str1); else write2xml(Report,"NA"); write2xml(Report,"</LatestPartQty>\n");
							write2xml(Report,"<PreviousPartQty>"); if(tc_strlen(LPMPart_pqty_Str2)>0) write2xml(Report,LPMPart_pqty_Str2); else write2xml(Report,"NA"); write2xml(Report,"</PreviousPartQty>\n");
							write2xml(Report,"<PartUOM>"); if(tc_strlen(LPMPart_puom_Str1)>0) write2xml(Report,LPMPart_puom_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartUOM>\n");
							write2xml(Report,"<PartInLib>"); if(tc_strlen(LPMPart_lib_Str1)>0) write2xml(Report,LPMPart_lib_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartInLib>\n");
							write2xml(Report,"<PartFreq>"); if(tc_strlen(LPMPart_vehfreq_Str1)>0) write2xml(Report,LPMPart_vehfreq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartFreq>\n");
							write2xml(Report,"<PartMaxDRAR>"); if(tc_strlen(LPMPart_vehmaxdrar_Str1)>0) write2xml(Report,LPMPart_vehmaxdrar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartMaxDRAR>\n");
							write2xml(Report,"<PartStatus>"); if(tc_strlen(partstatus)>0)write2xml(Report,partstatus); else write2xml(Report,"NA"); write2xml(Report,"</PartStatus>\n");
							write2xml(Report,"<PartData>"); if(tc_strlen(PartDataFile)>0) write2xml(Report,PartDataFile); else write2xml(Report,"NA"); write2xml(Report,"</PartData>\n");
							write2xml(Report,"</ChildDetails>\n");
					}
				}
				else 
				{
					printf("\n Master_File[Latest] is NULL..!!\n");fflush(stdout);
				}
				fclose(fp1LatestMaster_List);
				printf("\n File Compare [Latest with Previous] End..!!\n");fflush(stdout);
				
				printf("\n File Compare [Previous with Latest] Start..!!\n");fflush(stdout);
	            char *PLMPart_no_Str1 = NULL;
				char *PLMPart_rev_Str1 = NULL;
				char *PLMPart_seq_Str1 = NULL;
				char *PLMPart_desc_Str1 = NULL;
				char *PLMPart_add_Str1 = NULL;
				char *PLMPart_prod_Str1 = NULL;
				char *PLMPart_plat_Str1 = NULL;
				char *PLMPart_proj_Str1 = NULL;
				char *PLMPart_des_Str1 = NULL;
				char *PLMPart_drar_Str1 = NULL;
				char *PLMPart_ptype_Str1 = NULL;
				char *PLMPart_pqty_Str1 = NULL;
				char *PLMPart_puom_Str1 = NULL;
				char *PLMPart_lib_Str1 = NULL;
				char *PLMPart_vehfreq_Str1 = NULL;
				char *PLMPart_vehmaxdrar_Str1 = NULL;
				char *PLMPart_psdata_Str1 = NULL;
				FILE *fp2PreviousMaster_List = fopen(PreviousVCompFile, "r");
				char *PartDataFile2 = (char *) malloc(50*sizeof(char));
                if(fp2PreviousMaster_List != NULL)
				{
					printf("\n Master_File[Previous] Not Null..!!\n");fflush(stdout);
					while(fgets(Buffer3,MAX_LINE_LENGTH,fp2PreviousMaster_List)!=NULL)
                    {
                        PLMPart_no_Str1=strtok(Buffer3,"^");
						PLMPart_rev_Str1=strtok(NULL,"^");
						PLMPart_seq_Str1=strtok(NULL,"^");
						PLMPart_desc_Str1=strtok(NULL,"^");
						PLMPart_add_Str1=strtok(NULL,"^");
						PLMPart_prod_Str1=strtok(NULL,"^");
						PLMPart_plat_Str1=strtok(NULL,"^");
						PLMPart_proj_Str1=strtok(NULL,"^");
						PLMPart_des_Str1=strtok(NULL,"^");
						PLMPart_drar_Str1=strtok(NULL,"^");
						PLMPart_ptype_Str1=strtok(NULL,"^");
						PLMPart_pqty_Str1=strtok(NULL,"^");
						PLMPart_puom_Str1=strtok(NULL,"^");
						PLMPart_lib_Str1=strtok(NULL,"^");
						PLMPart_vehfreq_Str1=strtok(NULL,"^");
						PLMPart_vehmaxdrar_Str1=strtok(NULL,"^");
						PLMPart_psdata_Str1=strtok(NULL,"^");
                        if(PLMPart_no_Str1!=NULL)trimwhitespace(PLMPart_no_Str1);
						if(PLMPart_rev_Str1!=NULL)trimwhitespace(PLMPart_rev_Str1);
						if(PLMPart_seq_Str1!=NULL)trimwhitespace(PLMPart_seq_Str1);
						if(PLMPart_desc_Str1!=NULL)trimwhitespace(PLMPart_desc_Str1);
						if(PLMPart_add_Str1!=NULL)trimwhitespace(PLMPart_add_Str1);
					    //if(PLMPart_prod_Str1!=NULL)trimwhitespace(PLMPart_prod_Str1);
					    //if(PLMPart_plat_Str1!=NULL)trimwhitespace(PLMPart_plat_Str1);
						if(PLMPart_prod_Str1 != NULL)
						{
							STRNG_replace_str(PLMPart_prod_Str1,"&","&amp;",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,"<","&lt;",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,">","&gt;",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,","," ",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,";"," ",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,"\n"," ",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,"'"," ",&PLMPart_prod_Str1);
							STRNG_replace_str(PLMPart_prod_Str1,"/"," ",&PLMPart_prod_Str1);
						}
						if(PLMPart_plat_Str1 != NULL)
						{
							STRNG_replace_str(PLMPart_plat_Str1,"&","&amp;",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,"<","&lt;",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,">","&gt;",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,","," ",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,";"," ",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,"\n"," ",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,"'"," ",&PLMPart_plat_Str1);
							STRNG_replace_str(PLMPart_plat_Str1,"/"," ",&PLMPart_plat_Str1);
						}
						if(PLMPart_proj_Str1!=NULL)trimwhitespace(PLMPart_proj_Str1);
						if(PLMPart_des_Str1!=NULL)trimwhitespace(PLMPart_des_Str1);
						if(PLMPart_drar_Str1!=NULL)trimwhitespace(PLMPart_drar_Str1);
						if(PLMPart_ptype_Str1!=NULL)trimwhitespace(PLMPart_ptype_Str1);
						if(PLMPart_pqty_Str1!=NULL)trimwhitespace(PLMPart_pqty_Str1);
						if(PLMPart_puom_Str1!=NULL)trimwhitespace(PLMPart_puom_Str1);
						if(PLMPart_lib_Str1!=NULL)trimwhitespace(PLMPart_lib_Str1);
						if(PLMPart_vehfreq_Str1!=NULL)trimwhitespace(PLMPart_vehfreq_Str1);
						if(PLMPart_vehmaxdrar_Str1!=NULL)trimwhitespace(PLMPart_vehmaxdrar_Str1);
						if(PLMPart_psdata_Str1!=NULL)trimwhitespace(PLMPart_psdata_Str1);
                       
					    char *PLMPart_no_Str2 = NULL;
						char *PLMPart_rev_Str2 = NULL;
						char *PLMPart_seq_Str2 = NULL;
						char *PLMPart_desc_Str2 = NULL;
						char *PLMPart_add_Str2 = NULL;
						char *PLMPart_prod_Str2 = NULL;
						char *PLMPart_plat_Str2 = NULL;
						char *PLMPart_proj_Str2 = NULL;
						char *PLMPart_des_Str2 = NULL;
						char *PLMPart_drar_Str2 = NULL;
						char *PLMPart_ptype_Str2 = NULL;
						char *PLMPart_pqty_Str2 = NULL;
						char *PLMPart_puom_Str2 = NULL;
						char *PLMPart_lib_Str2 = NULL;
						char *PLMPart_vehfreq_Str2 = NULL;
				        char *PLMPart_vehmaxdrar_Str2 = NULL;
						char *PLMPart_psdata_Str2 = NULL;
						char* partstatus2 = NULL;
                        FILE *fp2LatestMaster_List = fopen(LatestVCompFile, "r");						
						if(fp2LatestMaster_List != NULL)
						{
							printf("\n Child_File[Latest] Not Null..!!\n");fflush(stdout);
							while(fgets(Buffer4,MAX_LINE_LENGTH,fp2LatestMaster_List)!=NULL)
							{
								PLMPart_no_Str2=strtok(Buffer4,"^");
								PLMPart_rev_Str2=strtok(NULL,"^");
								PLMPart_seq_Str2=strtok(NULL,"^");
								PLMPart_desc_Str2=strtok(NULL,"^");
								PLMPart_add_Str2=strtok(NULL,"^");
								PLMPart_prod_Str2=strtok(NULL,"^");
								PLMPart_plat_Str2=strtok(NULL,"^");
								PLMPart_proj_Str2=strtok(NULL,"^");
								PLMPart_des_Str2=strtok(NULL,"^");
								PLMPart_drar_Str2=strtok(NULL,"^");
								PLMPart_ptype_Str2=strtok(NULL,"^");
								PLMPart_pqty_Str2=strtok(NULL,"^");
								PLMPart_puom_Str2=strtok(NULL,"^");
								PLMPart_lib_Str2=strtok(NULL,"^");
								PLMPart_vehfreq_Str2=strtok(NULL,"^");
								PLMPart_vehmaxdrar_Str2=strtok(NULL,"^");
								PLMPart_psdata_Str2=strtok(NULL,"^");
								if(PLMPart_no_Str2!=NULL)trimwhitespace(PLMPart_no_Str2);
								if(PLMPart_rev_Str2!=NULL)trimwhitespace(PLMPart_rev_Str2);
								if(PLMPart_seq_Str2!=NULL)trimwhitespace(PLMPart_seq_Str2);
								if(PLMPart_desc_Str2!=NULL)trimwhitespace(PLMPart_desc_Str2);
								if(PLMPart_add_Str2!=NULL)trimwhitespace(PLMPart_add_Str2);
								//if(PLMPart_prod_Str2!=NULL)trimwhitespace(PLMPart_prod_Str2);
								//if(PLMPart_plat_Str2!=NULL)trimwhitespace(PLMPart_plat_Str2);
								if(PLMPart_prod_Str2 != NULL)
								{
									STRNG_replace_str(PLMPart_prod_Str2,"&","&amp;",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,"<","&lt;",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,">","&gt;",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,","," ",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,";"," ",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,"\n"," ",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,"'"," ",&PLMPart_prod_Str2);
									STRNG_replace_str(PLMPart_prod_Str2,"/"," ",&PLMPart_prod_Str2);
								}
								if(PLMPart_plat_Str2 != NULL)
								{
									STRNG_replace_str(PLMPart_plat_Str2,"&","&amp;",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,"<","&lt;",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,">","&gt;",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,","," ",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,";"," ",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,"\n"," ",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,"'"," ",&PLMPart_plat_Str2);
									STRNG_replace_str(PLMPart_plat_Str2,"/"," ",&PLMPart_plat_Str2);
								}
								if(PLMPart_proj_Str2!=NULL)trimwhitespace(PLMPart_proj_Str2);
								if(PLMPart_des_Str2!=NULL)trimwhitespace(PLMPart_des_Str2);
								if(PLMPart_drar_Str2!=NULL)trimwhitespace(PLMPart_drar_Str2);
								if(PLMPart_ptype_Str2!=NULL)trimwhitespace(PLMPart_ptype_Str2);
								if(PLMPart_pqty_Str2!=NULL)trimwhitespace(PLMPart_pqty_Str2);
								if(PLMPart_puom_Str2!=NULL)trimwhitespace(PLMPart_puom_Str2);
								if(PLMPart_lib_Str2!=NULL)trimwhitespace(PLMPart_lib_Str2);
								if(PLMPart_vehfreq_Str2!=NULL)trimwhitespace(PLMPart_vehfreq_Str2);
								if(PLMPart_vehmaxdrar_Str2!=NULL)trimwhitespace(PLMPart_vehmaxdrar_Str2);
								if(PLMPart_psdata_Str2!=NULL)trimwhitespace(PLMPart_psdata_Str2);
								if(tc_strcmp(PLMPart_no_Str1,PLMPart_no_Str2)==0)
								{
									goto jump2;
								}
							}
						}
						else 
						{
							printf("\n Child_File[Previous] is NULL..!!\n");fflush(stdout);
						}
						fclose(fp2LatestMaster_List);
						if(tc_strlen(partstatus2)>0)
						{
							printf("\n Already Updated..!!\n");fflush(stdout);
						}
						else
						{
							tc_strcpy(PartDataFile2,PLMPart_psdata_Str1);
							tc_strdup("Deleted",&partstatus2);
							write2xml(Report,"<ChildDetails>\n");
							write2xml(Report,"<PartNo>"); if(tc_strlen(PLMPart_no_Str1)>0) write2xml(Report,PLMPart_no_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartNo>\n");
							write2xml(Report,"<PartRev>"); if(tc_strlen(PLMPart_rev_Str1)>0) write2xml(Report,PLMPart_rev_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartRev>\n");
							write2xml(Report,"<PartSeq>"); if(tc_strlen(PLMPart_seq_Str1)>0) write2xml(Report,PLMPart_seq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartSeq>\n");
							write2xml(Report,"<PartDesc>"); if(tc_strlen(PLMPart_desc_Str1)>0) write2xml(Report,PLMPart_desc_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesc>\n");
							write2xml(Report,"<PartAddr>"); if(tc_strlen(PLMPart_add_Str1)>0) write2xml(Report,PLMPart_add_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartAddr>\n");
							write2xml(Report,"<PartProd>"); if(tc_strlen(PLMPart_prod_Str1)>0) write2xml(Report,PLMPart_prod_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProd>\n");
							write2xml(Report,"<PartPlat>"); if(tc_strlen(PLMPart_plat_Str1)>0) write2xml(Report,PLMPart_plat_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartPlat>\n");
							write2xml(Report,"<PartProj>"); if(tc_strlen(PLMPart_proj_Str1)>0) write2xml(Report,PLMPart_proj_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartProj>\n");
							write2xml(Report,"<PartDesGrp>"); if(tc_strlen(PLMPart_des_Str1)>0) write2xml(Report,PLMPart_des_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDesGrp>\n");
							write2xml(Report,"<PartDrAr>"); if(tc_strlen(PLMPart_drar_Str1)>0) write2xml(Report,PLMPart_drar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartDrAr>\n");
							write2xml(Report,"<PartType>"); if(tc_strlen(PLMPart_ptype_Str1)>0) write2xml(Report,PLMPart_ptype_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartType>\n");
							write2xml(Report,"<LatestPartQty>"); if(tc_strlen(PLMPart_pqty_Str2)>0) write2xml(Report,PLMPart_pqty_Str2); else write2xml(Report,"NA"); write2xml(Report,"</LatestPartQty>\n");
							write2xml(Report,"<PreviousPartQty>"); if(tc_strlen(PLMPart_pqty_Str1)>0) write2xml(Report,PLMPart_pqty_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PreviousPartQty>\n");
							write2xml(Report,"<PartUOM>"); if(tc_strlen(PLMPart_puom_Str1)>0) write2xml(Report,PLMPart_puom_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartUOM>\n");
							write2xml(Report,"<PartInLib>"); if(tc_strlen(PLMPart_lib_Str1)>0) write2xml(Report,PLMPart_lib_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartInLib>\n");
							write2xml(Report,"<PartFreq>"); if(tc_strlen(PLMPart_vehfreq_Str1)>0) write2xml(Report,PLMPart_vehfreq_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartFreq>\n");
							write2xml(Report,"<PartMaxDRAR>"); if(tc_strlen(PLMPart_vehmaxdrar_Str1)>0) write2xml(Report,PLMPart_vehmaxdrar_Str1); else write2xml(Report,"NA"); write2xml(Report,"</PartMaxDRAR>\n");
							write2xml(Report,"<PartStatus>"); if(tc_strlen(partstatus2)>0)write2xml(Report,partstatus2); else write2xml(Report,"NA"); write2xml(Report,"</PartStatus>\n");
							write2xml(Report,"<PartData>"); if(tc_strlen(PartDataFile2)>0) write2xml(Report,PartDataFile2); else write2xml(Report,"NA"); write2xml(Report,"</PartData>\n");
							write2xml(Report,"</ChildDetails>\n");
						}
						
						jump2:
						    printf("\n Already Matched So Exit..!!\n");fflush(stdout);
					}
				}
				else 
				{
					printf("\n Master_File[Previous] is NULL..!!\n");fflush(stdout);
				}
				fclose(fp2PreviousMaster_List);
				printf("\n File Compare [Previous with Latest] End..!!\n");fflush(stdout);
			}
			if((tc_strlen(latest_item_id_strDup)>0) && (tc_strcmp(previous_item_id_strDup,"Not_Present")==0))
			{
				printf(" Latest Item Revision is NR..!!\n");fflush(stdout);
			}
		}
		else
        {
			printf(" Latest Released Revision Found Zero[0] After Query[Latest Released Design Revision for ERC]..!!\n");fflush(stdout);
			tc_strdup("Not_Present",&latest_item_id_strDup);
			tc_strdup("Not_Present",&latest_item_revseq_strDup);
			tc_strdup("Not_Present",&latest_Veh_DescDup);
			tc_strdup("Not_Present",&latest_item_drar_strDup);
			tc_strdup("Not_Present",&previous_item_id_strDup);
			tc_strdup("Not_Present",&previous_item_revseq_strDup);
			tc_strdup("Not_Present",&previous_Veh_DescDup);
			tc_strdup("Not_Present",&previous_item_drar_strDup);
		}
	}
	else
    {
		printf(" Query[Latest Released Design Revision for ERC] Tag Not Found..!!\n");fflush(stdout);
		tc_strdup("Not_Present",&latest_item_id_strDup);
		tc_strdup("Not_Present",&latest_item_revseq_strDup);
		tc_strdup("Not_Present",&latest_Veh_DescDup);
		tc_strdup("Not_Present",&latest_item_drar_strDup);
		tc_strdup("Not_Present",&previous_item_id_strDup);
		tc_strdup("Not_Present",&previous_item_revseq_strDup);
		tc_strdup("Not_Present",&previous_Veh_DescDup);
		tc_strdup("Not_Present",&previous_item_drar_strDup);
    }
	write2xml(Report,"</VehCompare>\n");
	fclose(Report);
	printf(" Latest And Previous ERC Released Vehicles Compliance Report Generation End..!!\n");fflush(stdout);
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
	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");fflush(stdout);
	
    CLEANUP:
	ITK_CALL(ITK_exit_module(TRUE));	
	return ITK_ok;
}
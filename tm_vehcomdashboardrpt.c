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

int TC_VehCompDashboard(FILE* CVVarRpt)
{
	int iFail = ITK_ok;
	tag_t tItemobj = NULLTAG;
	int n_entries = 2;
	int n_itemobj_found = 0;
	tag_t* titemobj_results = NULLTAG;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
    tag_t Folder_tag = NULLTAG;
	char* FObjectName = NULL;
    char* FObjectType = NULL;
	int n_Items =0;
	tag_t* tItemObj = NULLTAG;
	char* ItemObjectType = NULL;
	char* ItemObjectName = NULL;
	char* ItemObjectDesc = NULL;
	char* Veh_No = NULL;
	char* Veh_Rev = NULL;
	char* Veh_Seq = NULL;
	char* Veh_Desc = NULL;
	char* Veh_Plat = NULL;
	char* Veh_DrAr = NULL;
	char* Veh_Total = NULL;
	char* Veh_Present = NULL;
	char* Veh_NotPresent = NULL;
	char* Veh_Above = NULL;
	char* Veh_Below = NULL;
	char* Veh_Max = NULL;
	char* Veh_All = NULL;
	char* Veh_Gen = NULL;
	char* Veh_Nodup = NULL;
	char* Veh_Revdup = NULL;
	char* Veh_Seqdup = NULL;
	char* Veh_Descdup = NULL;
	char* Veh_Platdup = NULL;
	char* Veh_DrArdup = NULL;
	char* Veh_Totaldup = NULL;
	char* Veh_Presentdup = NULL;
	char* Veh_NotPresentdup = NULL;
	char* Veh_Abovedup = NULL;
	char* Veh_Belowdup = NULL;
	char* Veh_Maxdup = NULL;
	char* Veh_Alldup = NULL;
	char* Veh_Gendup = NULL;
	
	printf("\n Finding Query[General...]..!!\n");fflush(stdout);
    ITK_CALL(QRY_find2("General...",&tItemobj));
	if(tItemobj != NULLTAG)
	{
		printf("\n Query [General...] Tag Found Successfully..!!\n");fflush(stdout);
		char *cEntries[2]  = {"Name","Type"};
		char *cValues[2]  = {"VEHICLE_SUBMODULE_COMPLIANCE_REPORT","Folder"};
		ITK_CALL(QRY_execute(tItemobj, n_entries, cEntries, cValues, &n_itemobj_found, &titemobj_results));
		printf("\n >>>>>>>>>>-------------------------------<<<<<<<<<<<\n");fflush(stdout);
		printf("\n Total Folder Found: [%d]\n",n_itemobj_found);fflush(stdout);
		printf("\n >>>>>>>>>>-------------------------------<<<<<<<<<<<\n");fflush(stdout);
		if(n_itemobj_found > 0)
		{
			Folder_tag = titemobj_results[0];
			ITK_CALL(AOM_UIF_ask_value(Folder_tag,"object_name",&FObjectName));
			printf("\n Object Name: [%s]\n",FObjectName);fflush(stdout);						
			ITK_CALL(AOM_ask_value_string(Folder_tag,"object_type",&FObjectType));
			printf("\n Object Type: [%s]\n",FObjectType);
			ITK_CALL(AOM_ask_value_tags(Folder_tag,"contents", &n_Items, &tItemObj));
			printf("\n >>>>>>>>>>-------------------------------<<<<<<<<<<<\n");fflush(stdout);
		    printf("\n Total Objects Found on Folder: [%d]\n",n_Items);fflush(stdout);
		    printf("\n >>>>>>>>>>-------------------------------<<<<<<<<<<<\n");fflush(stdout);
			if(n_Items > 0)
		    {
				printf("\n Total Objects Found on Folder Greater Than Zero[0]\n");fflush(stdout);
				for(i = 0; i < n_Items; i++)
				{
					ITK_CALL(AOM_ask_value_string(tItemObj[i],"object_type",&ItemObjectType));
					ITK_CALL(AOM_ask_value_string(tItemObj[i],"object_name",&ItemObjectName));
					ITK_CALL(AOM_ask_value_string(tItemObj[i],"object_desc",&ItemObjectDesc));
					printf("\n Item Object Type: [%s]",ItemObjectType);fflush(stdout);
					printf("\n Item Object Name: [%s]",ItemObjectName);fflush(stdout);
					printf("\n Item Object Description: [%s]",ItemObjectDesc);fflush(stdout);
					trimwhitespace(ItemObjectDesc);
					
					Veh_No=strtok(ItemObjectDesc,",");
			        Veh_Rev=strtok(NULL,",");
					Veh_Seq=strtok(NULL,",");
					Veh_Desc=strtok(NULL,",");
					Veh_Plat=strtok(NULL,",");
					Veh_DrAr=strtok(NULL,",");
					Veh_Total=strtok(NULL,",");
					Veh_Present=strtok(NULL,",");
					Veh_NotPresent=strtok(NULL,",");
					Veh_Above=strtok(NULL,",");
					Veh_Below=strtok(NULL,",");
					Veh_Max=strtok(NULL,",");
					Veh_All=strtok(NULL,",");
					Veh_Gen=strtok(NULL,",");
					
					if(Veh_No!=NULL)tc_strdup(Veh_No,&Veh_Nodup);
					if(Veh_Rev!=NULL)tc_strdup(Veh_Rev,&Veh_Revdup);
					if(Veh_Seq!=NULL)tc_strdup(Veh_Seq,&Veh_Seqdup);
					if(Veh_Desc!=NULL)tc_strdup(Veh_Desc,&Veh_Descdup);
					if(Veh_Descdup != NULL)
					{
						STRNG_replace_str(Veh_Descdup,"&","&amp;",&Veh_Descdup);
						STRNG_replace_str(Veh_Descdup,"<","&lt;",&Veh_Descdup);
						STRNG_replace_str(Veh_Descdup,">","&gt;",&Veh_Descdup);
						STRNG_replace_str(Veh_Descdup,"/"," ",&Veh_Descdup);
						STRNG_replace_str(Veh_Descdup,";"," ",&Veh_Descdup);
						STRNG_replace_str(Veh_Descdup,","," ",&Veh_Descdup);
					}
					if(Veh_Plat!=NULL)tc_strdup(Veh_Plat,&Veh_Platdup);
					if(Veh_DrAr!=NULL)tc_strdup(Veh_DrAr,&Veh_DrArdup);
					if(Veh_Total!=NULL)tc_strdup(Veh_Total,&Veh_Totaldup);
					if(Veh_Present!=NULL)tc_strdup(Veh_Present,&Veh_Presentdup);
					if(Veh_NotPresent!=NULL)tc_strdup(Veh_NotPresent,&Veh_NotPresentdup);
					if(Veh_Above!=NULL)tc_strdup(Veh_Above,&Veh_Abovedup);
					if(Veh_Below!=NULL)tc_strdup(Veh_Below,&Veh_Belowdup);
					if(Veh_Max!=NULL)tc_strdup(Veh_Max,&Veh_Maxdup);
					if(Veh_All!=NULL)tc_strdup(Veh_All,&Veh_Alldup);
					if(Veh_Gen!=NULL)tc_strdup(Veh_Gen,&Veh_Gendup);
					trimwhitespace(Veh_Nodup);
					printf("\n Vehicle No(Veh_Nodup): [%s]\n", Veh_Nodup);fflush(stdout);
					printf("\n Vehicle Rev(Veh_Revdup): [%s]\n", Veh_Revdup);fflush(stdout);
					printf("\n Vehicle Sequence(Veh_Seqdup): [%s]\n", Veh_Seqdup);fflush(stdout);
					printf("\n Vehicle Description(Veh_Descdup): [%s]\n", Veh_Descdup);fflush(stdout);
					printf("\n Vehicle Platform(Veh_Platdup): [%s]\n", Veh_Platdup);fflush(stdout);
					printf("\n Vehicle DR/AR(Veh_DrArdup): [%s]\n", Veh_DrArdup);fflush(stdout);
					printf("\n Vehicle Total(Veh_Totaldup): [%s]\n", Veh_Totaldup);fflush(stdout);
					printf("\n Vehicle Present(Veh_Presentdup): [%s]\n", Veh_Presentdup);fflush(stdout);
					printf("\n Vehicle Not Present(Veh_NotPresentdup): [%s]\n", Veh_NotPresentdup);fflush(stdout);
					printf("\n Vehicle Above(Veh_Abovedup): [%s]\n", Veh_Abovedup);fflush(stdout);
					printf("\n Vehicle Below(Veh_Belowdup): [%s]\n", Veh_Belowdup);fflush(stdout);
					printf("\n Vehicle Max(Veh_Maxdup): [%s]\n", Veh_Maxdup);fflush(stdout);
					printf("\n Vehicle All(Veh_Alldup): [%s]\n", Veh_Alldup);fflush(stdout);
					printf("\n Vehicle GenDate(Veh_Gendup): [%s]\n", Veh_Gendup);fflush(stdout);
					
					if(tc_strlen(Veh_Alldup)>0)
					{
						write2xml(CVVarRpt,"<VehCompDetails>\n");
						write2xml(CVVarRpt,"<VehNo>"); if(tc_strlen(Veh_Nodup)==9) write2xml(CVVarRpt,Veh_Nodup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehNo>\n");
						write2xml(CVVarRpt,"<VehRev>"); if(tc_strlen(Veh_Revdup)>0) write2xml(CVVarRpt,Veh_Revdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehRev>\n");
						write2xml(CVVarRpt,"<VehSeq>"); if(tc_strlen(Veh_Seqdup)>0) write2xml(CVVarRpt,Veh_Seqdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehSeq>\n");
						write2xml(CVVarRpt,"<VehDesc>"); if(tc_strlen(Veh_Descdup)>0) write2xml(CVVarRpt,Veh_Descdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehDesc>\n");
						write2xml(CVVarRpt,"<VehPlat>"); if(tc_strlen(Veh_Platdup)>0) write2xml(CVVarRpt,Veh_Platdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehPlat>\n");
						write2xml(CVVarRpt,"<VehDrAr>"); if(tc_strlen(Veh_DrArdup)>0) write2xml(CVVarRpt,Veh_DrArdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehDrAr>\n");
						write2xml(CVVarRpt,"<VehTotal>"); if(tc_strlen(Veh_Totaldup)>0) write2xml(CVVarRpt,Veh_Totaldup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehTotal>\n");
						write2xml(CVVarRpt,"<VehPresent>"); if(tc_strlen(Veh_Presentdup)>0) write2xml(CVVarRpt,Veh_Presentdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehPresent>\n");
						write2xml(CVVarRpt,"<VehNotPresent>"); if(tc_strlen(Veh_NotPresentdup)>0) write2xml(CVVarRpt,Veh_NotPresentdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehNotPresent>\n");
						write2xml(CVVarRpt,"<VehAbove>"); if(tc_strlen(Veh_Abovedup)>0) write2xml(CVVarRpt,Veh_Abovedup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehAbove>\n");
						write2xml(CVVarRpt,"<VehBelow>"); if(tc_strlen(Veh_Belowdup)>0) write2xml(CVVarRpt,Veh_Belowdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehBelow>\n");
						write2xml(CVVarRpt,"<VehMax>"); if(tc_strlen(Veh_Maxdup)>0) write2xml(CVVarRpt,Veh_Maxdup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehMax>\n");
						write2xml(CVVarRpt,"<VehAll>"); if(tc_strlen(Veh_Alldup)>0) write2xml(CVVarRpt,Veh_Alldup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</VehAll>\n");
						write2xml(CVVarRpt,"<GenStamp>"); if(tc_strlen(Veh_Gendup)>0) write2xml(CVVarRpt,Veh_Gendup); else write2xml(CVVarRpt,"NA"); write2xml(CVVarRpt,"</GenStamp>\n");
						write2xml(CVVarRpt,"</VehCompDetails>\n");
                    }
                    else
                    {
						printf("\n !!!!!!!!!!!!!!!! Junk Value Data !!!!!!!!!!!!!!!! \n");fflush(stdout);
					}						
				}
			}
			else
			{
				printf(" No Objects Found in Searched Folder..!!\n");fflush(stdout);
			}
		}
		else
		{
			printf(" Searched Folder Not Found..!!\n");fflush(stdout);
		}
	}
	else
	{
		printf(" [General...] Query Tag Not Found..!!\n");fflush(stdout);
	}
	
	return iFail;
}
int ITK_user_main(int argc,char* argv[]) 
{
	char *message;
	char *loggedInUser = NULL;
    
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
		printf(" Auto Login Successfull..!!\n");fflush(stdout);
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
	
	printf("\n Generating XML Report File Name..!!");fflush(stdout);
	Report = fopen("/tmp/VehComplianceDashboardReport.xml","w");
	if(Report == NULL)
	{
		printf("ERROR: Unable To Open XML File..!!\n");
		return -1;
	}
	else
	{
		printf("XML File Opened Successfully..!!\n");
	}

	strftime(GenDate,100,"%d-%m-%Y %H:%M:%S",&when);
	write2xml(Report,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	write2xml(Report,"<VehCompDashboard>\n");
	printf("\n >>>>>>>>>>111111111111111111111111111111111111111111111111111111111111111111111111<<<<<<<<<<<\n");fflush(stdout);
	printf("\n Function1: Vehicle Compliance Details Print Start");fflush(stdout);
	TC_VehCompDashboard(Report);
	printf("\n Function1: Vehicle Compliance Details Print End\n");fflush(stdout);
	printf("\n >>>>>>>>>>111111111111111111111111111111111111111111111111111111111111111111111111<<<<<<<<<<<\n");fflush(stdout);
	write2xml(Report,"</VehCompDashboard>\n");
	fclose(Report);
	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");fflush(stdout);
	
    CLEANUP:
	ITK_CALL(ITK_exit_module(TRUE));	
	return ITK_ok;
}
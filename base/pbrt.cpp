#include "pbrt.h"
#include "..\cdep\pbni.h"

typedef PBXRESULT (*P_PB_GetVM)(IPB_VM** vm);

char* test(){
    IPB_Session* session;   
	IPB_VM* pbvm = NULL;    //Load the PowerBuilder VM module   
	HINSTANCE hinst = LoadLibraryA("pbvm90.dll");   
	//printf("Loaded PBVM successfully\n%d",FeilExists("pbvm90.dll"));
	if ( hinst== NULL)   return (char*)"Error in CreateSession\n";   
    printf("Loaded PBVM successfully\n");
	P_PB_GetVM getvm = (P_PB_GetVM)GetProcAddress      (hinst,"PB_GetVM");  
	if (getvm == NULL) return (char*)"Error in CreateSession\n";    
	getvm(&pbvm);  
	if (pbvm == NULL) return (char*)"Error in CreateSession\n";
	LPCTSTR LibList[] = {_T("E:\\lswork\\pb\\src\\pbruntime\\main.pbl"),_T("E:\\lswork\\pb\\src\\pbruntime\\temp.pbl")};   
	if ( pbvm->CreateSession(_T("main"), LibList, 1,      &session) != PBX_OK )  
	{    
	    fprintf(stderr, "Error in CreateSession\n");    
	    return (char*)"Error in CreateSession\n";  
	}
	pbgroup group = session->FindGroup(_T("u1"),pbgroup_userobject);  
	if (group == NULL)   return (char*)"Error in CreateSession\n";      // Now find the class nvo_mult in the group   
    pbfieldID fid = session->GetGlobalVarID(_T("gs_pb"));
    session->SetStringGlobalVar(fid,_T("2.0.0"));
	pbclass cls = session->FindClass(group,_T("u1"));  
	if (cls == NULL)  return (char*)"Error in CreateSession\n";     // Create an instance of the PowerBuilder object  
	pbobject pbobj = session->NewObject(cls);
	//pbgroup group = session->FindGroup("gf_version", pbgroup_function); 
	// To call the class member function f_mult,    // pass its signature as the last argument   // to GetMethodID    
	pbmethodID mid = session->GetMethodID(cls,_T("hello"), PBRT_FUNCTION, _T(""));    // Initialize call info structure based on method ID  
	PBCallInfo ci;    
	session->InitCallInfo(cls, mid, &ci);
	ci.pArgs-> GetAt(0)->SetString(_T("aaaaaaaa°¡°¡°¡aaaaaaa"));  
	session->InvokeObjectFunction(pbobj, mid, &ci);
	pbstring ret = ci.returnValue->GetString();   
	char* m = (char*)malloc(255*sizeof(char));
    sprintf(m, "%s", session->GetString(ret));  
	session->Release();
    FreeLibrary(hinst);
    return m;
}

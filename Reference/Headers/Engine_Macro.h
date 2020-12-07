#pragma once




#define _USING(NAME) using namespace NAME;
#define _BEGIN(NAME) namespace NAME{
#define _END		 }

#define PURE =0

#define _MSGBOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("Error"), MB_OK);


#ifdef ENGINE_EXPORTS

#define _DLLEXPORTS _declspec(dllexport)
#else
#define _DLLEXPORTS _declspec(dllimport)
#endif


#define NO_COPY(CLASSNAME)								\
	private:											\
	CLASSNAME(const CLASSNAME&);						\
	CLASSNAME& operator = (const CLASSNAME&);			

#define DECLARE_SINGLETON(CLASSNAME)					\
	NO_COPY(CLASSNAME)									\
	private:											\
	static CLASSNAME*	m_pInstance;					\
	public:												\
	static CLASSNAME*	GetInstance( void );			\
	static unsigned int DestroyInstance( void );				

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
	CLASSNAME*	CLASSNAME::m_pInstance = NULL;			\
	CLASSNAME*	CLASSNAME::GetInstance( void )	{		\
		if(NULL == m_pInstance) {						\
			m_pInstance = new CLASSNAME;				\
		}												\
		return m_pInstance;								\
	}													\
	unsigned int CLASSNAME::DestroyInstance( void ) {	\
		unsigned int dwRefCnt=0;						\
		if(NULL != m_pInstance)	{						\
			dwRefCnt= m_pInstance->Release();			\
			if(dwRefCnt==0)								\
				m_pInstance = NULL;						\
		}												\
		return dwRefCnt;								\
	}
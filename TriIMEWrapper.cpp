#include "StdAfx.h"

#if IME_ENABLED

#include "triimewrapper.h"

HINSTANCE TriIMEWrapper::s_hDllImm32;      // IMM32 DLL handle
HINSTANCE TriIMEWrapper::s_hDllVer;        // Version DLL handle
HKL       TriIMEWrapper::s_hklCurrent;     // Current keyboard layout of the process
HINSTANCE TriIMEWrapper::s_hDllIme;           // Instance handle of the current IME module
HIMC      TriIMEWrapper::s_hImcDef;           // Default input context

// Function pointers
INPUTCONTEXT* (WINAPI * TriIMEWrapper::m_fpImmLockIMC)(HIMC hIMC) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmUnlockIMC)(HIMC hIMC) = NULL;
LPVOID (WINAPI * TriIMEWrapper::m_fpImmLockIMCC)(HIMCC hIMC) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmUnlockIMCC)(HIMCC hIMC) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmDisableTextFrameService)(DWORD idThread) = NULL;
LONG (WINAPI * TriIMEWrapper::m_fpImmGetCompositionStringW)(HIMC hIMC, DWORD dwIndex, LPVOID lpBuf, DWORD dwBufLen) = NULL;
DWORD (WINAPI * TriIMEWrapper::m_fpImmGetCandidateListW)(HIMC hIMC, DWORD dwIndex, LPCANDIDATELIST lpCandList, DWORD dwBufLen) = NULL;
HIMC (WINAPI * TriIMEWrapper::m_fpImmGetContext)(HWND hWnd) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmReleaseContext)(HWND hWnd, HIMC hIMC) = NULL;
HIMC (WINAPI * TriIMEWrapper::m_fpImmAssociateContext)(HWND hWnd, HIMC hIMC) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmGetOpenStatus)(HIMC hIMC) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmSetOpenStatus)(HIMC hIMC, BOOL fOpen) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmGetConversionStatus)(HIMC hIMC, LPDWORD lpfdwConversion, LPDWORD lpfdwSentence) = NULL;
DWORD (WINAPI * TriIMEWrapper::m_fpImmGetConversionListW)(HKL hKL, HIMC hIMC, LPCWSTR lpSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen, UINT uFlag) = NULL;
HWND (WINAPI * TriIMEWrapper::m_fpImmGetDefaultIMEWnd)(HWND hWnd) = NULL;
UINT (WINAPI * TriIMEWrapper::m_fpImmGetIMEFileNameA)(HKL hKL, LPSTR lpszFileName, UINT uBufLen) = NULL;
UINT (WINAPI * TriIMEWrapper::m_fpImmGetVirtualKey)(HWND hWnd) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmNotifyIME)(HIMC hIMC, DWORD dwAction, DWORD dwIndex, DWORD dwValue) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmSetConversionStatus)(HIMC hIMC, DWORD fdwConversion, DWORD fdwSentence) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmSimulateHotKey)(HWND hWnd, DWORD dwHotKeyID) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpImmIsIME)(HKL hKL) = NULL;
DWORD (WINAPI * TriIMEWrapper::m_fpImmGetGuideLineW)(HIMC hIMC, DWORD dwIndex, LPWSTR lpBuf, DWORD dwBufLen) = NULL;
BOOL  (WINAPI *TriIMEWrapper::m_fpImmSetCompositionStringW)(HIMC hIMC, DWORD dwIndex, LPVOID lpComp, DWORD dwCompLen, LPVOID lpRead, DWORD dwReadLen) = NULL;

// Traditional Chinese IME
UINT (WINAPI * TriIMEWrapper::m_fpGetReadingString)(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBufLen, PINT pnErrorIndex, BOOL * pfIsVertical, PUINT puMaxReadingLen) = NULL;
BOOL (WINAPI * TriIMEWrapper::m_fpShowReadingWindow)(HIMC himc, BOOL bShow) = NULL;
// Function pointers: Verion library imports
BOOL (APIENTRY * TriIMEWrapper::m_fpVerQueryValueA)(const LPVOID pBlock, LPSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen) = NULL;
BOOL (APIENTRY * TriIMEWrapper::m_fpGetFileVersionInfoA)(LPSTR lpstFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) = NULL;
DWORD (APIENTRY * TriIMEWrapper::m_fpGetFileVersionInfoSizeA)(LPSTR lpstrFilename, LPDWORD lpdwHandle) = NULL;

TriIMEWrapper::TriIMEWrapper(void)
{
	TriIMEWrapper::InitializeImm();
}

TriIMEWrapper::~TriIMEWrapper(void)
{
	TriIMEWrapper::UninitializeImm();
}

void TriIMEWrapper::InitializeImm()
{
	CHAR szPath[MAX_PATH+1];
    if (!::GetSystemDirectory(szPath, MAX_PATH+1 ))
        return;
    lstrcat(szPath, IMM32_DLLNAME);
    s_hDllImm32 = LoadLibrary(szPath);
    if (s_hDllImm32)
    {
		*((FARPROC*)&m_fpImmLockIMC) = ::GetProcAddress(s_hDllImm32, "ImmLockIMC");
		*((FARPROC*)&m_fpImmUnlockIMC) = ::GetProcAddress(s_hDllImm32, "ImmUnlockIMC");
		*((FARPROC*)&m_fpImmLockIMCC) = ::GetProcAddress(s_hDllImm32, "ImmLockIMCC");
		*((FARPROC*)&m_fpImmUnlockIMCC) = ::GetProcAddress(s_hDllImm32, "ImmUnlockIMCC");
		*((FARPROC*)&m_fpImmDisableTextFrameService) = ::GetProcAddress(s_hDllImm32, "ImmDisableTextFrameService");
		*((FARPROC*)&m_fpImmGetCompositionStringW) = ::GetProcAddress(s_hDllImm32, "ImmGetCompositionStringW");
		*((FARPROC*)&m_fpImmGetCandidateListW) = ::GetProcAddress(s_hDllImm32, "ImmGetCandidateListW");
		*((FARPROC*)&m_fpImmGetContext) = ::GetProcAddress(s_hDllImm32, "ImmGetContext");
		*((FARPROC*)&m_fpImmReleaseContext) = ::GetProcAddress(s_hDllImm32, "ImmReleaseContext");
		*((FARPROC*)&m_fpImmAssociateContext) = ::GetProcAddress(s_hDllImm32, "ImmAssociateContext");
		*((FARPROC*)&m_fpImmGetOpenStatus) = ::GetProcAddress(s_hDllImm32, "ImmGetOpenStatus");
		*((FARPROC*)&m_fpImmSetOpenStatus) = ::GetProcAddress(s_hDllImm32, "ImmSetOpenStatus");
		*((FARPROC*)&m_fpImmGetConversionStatus) = ::GetProcAddress(s_hDllImm32, "ImmGetConversionStatus");
		*((FARPROC*)&m_fpImmGetConversionListW) = ::GetProcAddress(s_hDllImm32, "ImmGetConversionListW");
		*((FARPROC*)&m_fpImmGetDefaultIMEWnd) = ::GetProcAddress(s_hDllImm32, "ImmGetDefaultIMEWnd");
		*((FARPROC*)&m_fpImmGetIMEFileNameA) = ::GetProcAddress(s_hDllImm32, "ImmGetIMEFileNameA");
		*((FARPROC*)&m_fpImmGetVirtualKey) = ::GetProcAddress(s_hDllImm32, "ImmGetVirtualKey");
		*((FARPROC*)&m_fpImmNotifyIME) = ::GetProcAddress(s_hDllImm32, "ImmNotifyIME");
		*((FARPROC*)&m_fpImmSetConversionStatus) = ::GetProcAddress(s_hDllImm32, "ImmSetConversionStatus");
		*((FARPROC*)&m_fpImmSimulateHotKey) = ::GetProcAddress(s_hDllImm32, "ImmSimulateHotKey");
		*((FARPROC*)&m_fpImmIsIME) = ::GetProcAddress(s_hDllImm32, "ImmIsIME");
		*((FARPROC*)&m_fpImmGetGuideLineW) = ::GetProcAddress(s_hDllImm32, "ImmGetGuideLineW");
		*((FARPROC*)&m_fpImmSetCompositionStringW) = ::GetProcAddress(s_hDllImm32, "ImmSetCompositionStringW");
    }

    if (!::GetSystemDirectory(szPath, MAX_PATH+1))
        return;
    lstrcat(szPath, VER_DLLNAME);
    s_hDllVer = LoadLibrary(szPath);
    if( s_hDllVer )
    {
		*((FARPROC*)&m_fpVerQueryValueA) = ::GetProcAddress(s_hDllVer, "VerQueryValueA");
		*((FARPROC*)&m_fpGetFileVersionInfoA) = ::GetProcAddress(s_hDllVer, "GetFileVersionInfoA");
		*((FARPROC*)&m_fpGetFileVersionInfoSizeA) = ::GetProcAddress(s_hDllVer, "GetFileVersionInfoSizeA");
    }
}


void TriIMEWrapper::UninitializeImm()
{
    if( s_hDllImm32 )
    {
        m_fpImmLockIMC = NULL;
        m_fpImmUnlockIMC = NULL;
        m_fpImmLockIMCC = NULL;
        m_fpImmUnlockIMCC = NULL;
        m_fpImmDisableTextFrameService = NULL;
        m_fpImmGetCompositionStringW = NULL;
        m_fpImmGetCandidateListW = NULL;
        m_fpImmGetContext = NULL;
        m_fpImmReleaseContext = NULL;
        m_fpImmAssociateContext = NULL;
        m_fpImmGetOpenStatus = NULL;
        m_fpImmSetOpenStatus = NULL;
        m_fpImmGetConversionStatus = NULL;
        m_fpImmGetDefaultIMEWnd = NULL;
        m_fpImmGetIMEFileNameA = NULL;
        m_fpImmGetVirtualKey = NULL;
        m_fpImmNotifyIME = NULL;
        m_fpImmSetConversionStatus = NULL;
        m_fpImmSimulateHotKey = NULL;
        m_fpImmIsIME = NULL;
		m_fpImmGetGuideLineW = NULL;
		m_fpImmSetCompositionStringW = NULL;

        FreeLibrary( s_hDllImm32 );
        s_hDllImm32 = NULL;
    }
    if( s_hDllIme )
    {
        m_fpGetReadingString = NULL;
        m_fpShowReadingWindow = NULL;

        FreeLibrary( s_hDllIme );
        s_hDllIme = NULL;
    }
    if( s_hDllVer )
    {
        m_fpVerQueryValueA = NULL;
        m_fpGetFileVersionInfoA = NULL;
        m_fpGetFileVersionInfoSizeA = NULL;

        FreeLibrary( s_hDllVer );
        s_hDllVer = NULL;
    }
}

//--------------------------------------------------------------------------------------
// Sets up IME-specific APIs for the IME edit controls.  This is called every time
// the input locale changes.
void TriIMEWrapper::SetupImeApi()
{
    char szImeFile[MAX_PATH + 1];

    m_fpGetReadingString = NULL;
    m_fpShowReadingWindow = NULL;

	s_hklCurrent = GetKeyboardLayout(::GetCurrentThreadId());

    if (ImmGetIMEFileNameA(s_hklCurrent, szImeFile, sizeof(szImeFile)/sizeof(szImeFile[0]) - 1) == 0)
        return;

    if (s_hDllIme)
		FreeLibrary(s_hDllIme);

    s_hDllIme = LoadLibraryA(szImeFile);
    if (!s_hDllIme)
        return;

	*((FARPROC*)&m_fpGetReadingString) = ::GetProcAddress(s_hDllIme, "GetReadingString");
	*((FARPROC*)&m_fpShowReadingWindow) = ::GetProcAddress(s_hDllIme, "ShowReadingWindow");
}

INPUTCONTEXT* TriIMEWrapper::ImmLockIMC(HIMC hIMC)
{
	if (NULL != m_fpImmLockIMC)
		return m_fpImmLockIMC(hIMC);
	return NULL;
}

BOOL TriIMEWrapper::ImmUnlockIMC(HIMC hIMC)
{
	if (NULL != m_fpImmUnlockIMC)
		return m_fpImmUnlockIMC(hIMC);
	return FALSE;
}

LPVOID TriIMEWrapper::ImmLockIMCC(HIMCC hIMCC)
{
	if (NULL != m_fpImmLockIMCC)
		return m_fpImmLockIMCC(hIMCC);
	return NULL;
}

BOOL TriIMEWrapper::ImmUnlockIMCC(HIMCC hIMCC)
{
	if (NULL != m_fpImmUnlockIMCC)
		return m_fpImmUnlockIMCC(hIMCC);
	return FALSE;
}

BOOL TriIMEWrapper::ImmDisableTextFrameService(DWORD idThread)
{
	if (NULL != m_fpImmDisableTextFrameService)
		return m_fpImmDisableTextFrameService(idThread);
	return TRUE;
}

LONG TriIMEWrapper::ImmGetCompositionStringW(HIMC hIMC, DWORD dwIndex, LPVOID lpBuf, DWORD dwBufLen)
{
	if (NULL != m_fpImmGetCompositionStringW)
		return m_fpImmGetCompositionStringW(hIMC, dwIndex, lpBuf, dwBufLen);
	return IMM_ERROR_GENERAL;
}

DWORD TriIMEWrapper::ImmGetCandidateListW(HIMC hIMC, DWORD dwIndex, LPCANDIDATELIST lpCandList, DWORD dwBufLen)
{
	if (NULL != m_fpImmGetCandidateListW)
		return m_fpImmGetCandidateListW(hIMC, dwIndex, lpCandList, dwBufLen);
	return 0;
}

HIMC TriIMEWrapper::ImmGetContext(HWND hWnd)
{
	if (NULL != m_fpImmGetContext)
		return m_fpImmGetContext(hWnd);
	return NULL;
}

BOOL TriIMEWrapper::ImmReleaseContext(HWND hWnd, HIMC hIMC)
{
	if (NULL != m_fpImmReleaseContext)
		return m_fpImmReleaseContext(hWnd, hIMC);
	return FALSE;
}

HIMC TriIMEWrapper::ImmAssociateContext(HWND hWnd, HIMC hIMC)
{
	if (NULL != m_fpImmAssociateContext)
		return m_fpImmAssociateContext(hWnd, hIMC);
	return NULL;
}

BOOL TriIMEWrapper::ImmGetOpenStatus(HIMC hIMC)
{
	if (NULL != m_fpImmGetOpenStatus)
		return m_fpImmGetOpenStatus(hIMC);
	return 0;
}

BOOL TriIMEWrapper::ImmSetOpenStatus(HIMC hIMC, BOOL fOpen)
{
	if (NULL != m_fpImmSetOpenStatus)
		return m_fpImmSetOpenStatus(hIMC, fOpen);
	return 0;
}

BOOL TriIMEWrapper::ImmGetConversionStatus(HIMC hIMC, LPDWORD lpfdwConversion, LPDWORD lpfdwSentence)
{
	if (NULL != m_fpImmGetConversionStatus)
		return m_fpImmGetConversionStatus(hIMC, lpfdwConversion, lpfdwSentence);
	return 0;
}

DWORD TriIMEWrapper::ImmGetConversionListW(HKL hKL, HIMC hIMC, LPCWSTR lpSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen, UINT uFlag)
{
	if (NULL != m_fpImmGetConversionListW)
		return m_fpImmGetConversionListW(hKL, hIMC, lpSrc, lpDst, dwBufLen, uFlag);
	return 0;
}

HWND TriIMEWrapper::ImmGetDefaultIMEWnd(HWND hWnd)
{
	if (NULL != m_fpImmGetDefaultIMEWnd)
		return m_fpImmGetDefaultIMEWnd(hWnd);
	return NULL;
}

UINT TriIMEWrapper::ImmGetIMEFileNameA(HKL hKL, LPSTR lpszFileName, UINT uBufLen)
{
	if (NULL != m_fpImmGetIMEFileNameA)
		return m_fpImmGetIMEFileNameA(hKL, lpszFileName, uBufLen);
	return 0;
}

UINT TriIMEWrapper::ImmGetVirtualKey(HWND hWnd)
{
	if (NULL != m_fpImmGetVirtualKey)
		return m_fpImmGetVirtualKey(hWnd);
	return 0;
}

BOOL TriIMEWrapper::ImmNotifyIME(HIMC hIMC, DWORD dwAction, DWORD dwIndex, DWORD dwValue)
{
	if (NULL != m_fpImmNotifyIME)
		return m_fpImmNotifyIME(hIMC, dwAction, dwIndex, dwValue);
	return FALSE;
}

BOOL TriIMEWrapper::ImmSetConversionStatus(HIMC hIMC, DWORD fdwConversion, DWORD fdwSentence)
{
	if (NULL != m_fpImmSetConversionStatus)
		return m_fpImmSetConversionStatus(hIMC, fdwConversion, fdwSentence);
	return FALSE;
}

BOOL TriIMEWrapper::ImmSimulateHotKey(HWND hWnd, DWORD dwHotKeyID)
{
	if (NULL != m_fpImmSimulateHotKey)
		return m_fpImmSimulateHotKey(hWnd, dwHotKeyID);
	return FALSE;
}

BOOL TriIMEWrapper::ImmIsIME(HKL hKL)
{
	if (NULL != m_fpImmIsIME)
		return m_fpImmIsIME(hKL);
	return FALSE;
}

DWORD TriIMEWrapper::ImmGetGuideLineW(HIMC hIMC, DWORD dwIndex, LPWSTR lpBuf, DWORD dwBufLen)
{
	if (NULL != m_fpImmGetGuideLineW)
		return m_fpImmGetGuideLineW(hIMC, dwIndex, lpBuf, dwBufLen);
	return GL_LEVEL_NOGUIDELINE;
}

BOOL TriIMEWrapper::ImmSetCompositionStringW(HIMC hIMC, DWORD dwIndex, LPVOID lpComp, DWORD dwCompLen, LPVOID lpRead, DWORD dwReadLen)
{
	if (NULL != m_fpImmSetCompositionStringW)
		return m_fpImmSetCompositionStringW(hIMC, dwIndex, lpComp, dwCompLen, lpRead, dwReadLen);
	return FALSE;
}

#ifndef LCID_INVARIANT
// We define the locale-invariant ID ourselves since it doesn't exist prior to WinXP
// For more information, see the CompareString() reference.
#define LCID_INVARIANT MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)
#endif // LCID_INVARIANT

DWORD TriIMEWrapper::GetImeId(UINT uIndex)
{
    static HKL hklPrev = 0;
    static DWORD dwID[2] = {0, 0};  // Cache the result
    
    DWORD   dwVerSize;
    DWORD   dwVerHandle;
    LPVOID  lpVerBuffer;
    LPVOID  lpVerData;
    UINT    cbVerData;
    char    szTmp[1024];

    if (uIndex >= sizeof(dwID) / sizeof(dwID[0]))
        return 0;

    if (hklPrev == s_hklCurrent)
        return dwID[uIndex];

    hklPrev = s_hklCurrent;  // Save for the next invocation

    // Check if we are using an older Chinese IME
    if (!((s_hklCurrent == _CHT_HKL)||(s_hklCurrent == _CHT_HKL2)||(s_hklCurrent == _CHS_HKL)))
    {
        dwID[0] = dwID[1] = 0;
        return dwID[uIndex];
    }

    // Obtain the IME file name
    if (!ImmGetIMEFileNameA(s_hklCurrent, szTmp, (sizeof(szTmp) / sizeof(szTmp[0])) - 1))
    {
        dwID[0] = dwID[1] = 0;
        return dwID[uIndex];
    }

    // Check for IME that doesn't implement reading string API
    if (!m_fpGetReadingString)
    {
        if ((CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTmp, -1, CHT_IMEFILENAME1, -1) != CSTR_EQUAL) &&
            (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTmp, -1, CHT_IMEFILENAME2, -1) != CSTR_EQUAL) &&
            (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTmp, -1, CHT_IMEFILENAME3, -1) != CSTR_EQUAL) &&
            (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTmp, -1, CHS_IMEFILENAME1, -1) != CSTR_EQUAL) &&
            (CompareStringA(LCID_INVARIANT, NORM_IGNORECASE, szTmp, -1, CHS_IMEFILENAME2, -1) != CSTR_EQUAL))
        {
            dwID[0] = dwID[1] = 0;
            return dwID[uIndex];
        }
    }

    dwVerSize = GetFileVersionInfoSizeA(szTmp, &dwVerHandle);
    if (dwVerSize)
    {
        lpVerBuffer = HeapAlloc(GetProcessHeap(), 0, dwVerSize);
        if (lpVerBuffer)
        {
            if (GetFileVersionInfoA(szTmp, dwVerHandle, dwVerSize, lpVerBuffer))
            {
                if (VerQueryValueA(lpVerBuffer, "\\", &lpVerData, &cbVerData))
                {
                    DWORD dwVer = ((VS_FIXEDFILEINFO*)lpVerData )->dwFileVersionMS;
                    dwVer = (dwVer & 0x00ff0000) << 8 | (dwVer & 0x000000ff) << 16;
                    if (m_fpGetReadingString
                        ||
                        (GetLanguage() == LANG_CHT &&
                          ( dwVer == MAKEIMEVERSION(4, 2) || 
                            dwVer == MAKEIMEVERSION(4, 3) || 
                            dwVer == MAKEIMEVERSION(4, 4) || 
                            dwVer == MAKEIMEVERSION(5, 0) ||
                            dwVer == MAKEIMEVERSION(5, 1) ||
                            dwVer == MAKEIMEVERSION(5, 2) ||
                            dwVer == MAKEIMEVERSION(6, 0)))
                        ||
                        (GetLanguage() == LANG_CHS &&
                          ( dwVer == MAKEIMEVERSION(4, 1) ||
                            dwVer == MAKEIMEVERSION(4, 2) ||
                            dwVer == MAKEIMEVERSION(5, 3)))
                      )
                    {
                        dwID[0] = dwVer | GetLanguage();
                        dwID[1] = ((VS_FIXEDFILEINFO*)lpVerData)->dwFileVersionLS;
                    }
                }
            }
            HeapFree(GetProcessHeap(), 0, lpVerBuffer);
        }
    }

    return dwID[uIndex];
}

// Function pointers: Traditional Chinese IME
UINT TriIMEWrapper::GetReadingString(HIMC himc, UINT uReadingBufLen, LPWSTR lpwReadingBufLen, PINT pnErrorIndex, BOOL * pfIsVertical, PUINT puMaxReadingLen)
{
	if (NULL != m_fpGetReadingString)
		return m_fpGetReadingString(himc, uReadingBufLen, lpwReadingBufLen, pnErrorIndex, pfIsVertical, puMaxReadingLen);
	return 0;
}

BOOL TriIMEWrapper::ShowReadingWindow(HIMC himc, BOOL bShow)
{
	if (NULL != m_fpShowReadingWindow)
		return m_fpShowReadingWindow(himc, bShow);
	return FALSE;
}

// Function pointers: Verion library imports
BOOL TriIMEWrapper::VerQueryValueA(const LPVOID pBlock, LPSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen)
{
	if (NULL != m_fpVerQueryValueA)
		return m_fpVerQueryValueA(pBlock, lpSubBlock, lplpBuffer, puLen);
	return 0;
}

BOOL TriIMEWrapper::GetFileVersionInfoA(LPSTR lpstFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
	if (NULL != m_fpGetFileVersionInfoA)
		return m_fpGetFileVersionInfoA(lpstFilename, dwHandle, dwLen, lpData);
	return 0;
}

DWORD TriIMEWrapper::GetFileVersionInfoSizeA(LPSTR lpstrFilename, LPDWORD lpdwHandle)
{
	if (NULL != m_fpGetFileVersionInfoSizeA)
		return m_fpGetFileVersionInfoSizeA(lpstrFilename, lpdwHandle);
	return 0;
}

bool TriIMEWrapper::GetReadingWindowOrientation(DWORD dwId)
{
    bool s_bHorizontalReading = ( s_hklCurrent == _CHS_HKL ) || ( s_hklCurrent == _CHT_HKL2 ) || ( dwId == 0 );
    if( !s_bHorizontalReading && ( dwId & 0x0000FFFF ) == LANG_CHT )
    {
        CHAR szRegPath[MAX_PATH];
        HKEY hKey;
        DWORD dwVer = dwId & 0xFFFF0000;
        lstrcpy( szRegPath, "software\\microsoft\\windows\\currentversion\\" );
        lstrcat( szRegPath, ( dwVer >= MAKEIMEVERSION( 5, 1 ) ) ? "MSTCIPH" : "TINTLGNT" );
        LONG lRc = RegOpenKeyEx( HKEY_CURRENT_USER, szRegPath, 0, KEY_READ, &hKey );
        if (lRc == ERROR_SUCCESS)
        {
            DWORD dwSize = sizeof(DWORD), dwMapping, dwType;
            lRc = RegQueryValueEx( hKey, "Keyboard Mapping", NULL, &dwType, (PBYTE)&dwMapping, &dwSize );
            if (lRc == ERROR_SUCCESS)
            {
                if ( ( dwVer <= MAKEIMEVERSION( 5, 0 ) && 
                       ( (BYTE)dwMapping == 0x22 || (BYTE)dwMapping == 0x23 ) )
                     ||
                     ( ( dwVer == MAKEIMEVERSION( 5, 1 ) || dwVer == MAKEIMEVERSION( 5, 2 ) ) &&
                       (BYTE)dwMapping >= 0x22 && (BYTE)dwMapping <= 0x24 )
                   )
                {
                    s_bHorizontalReading = true;
                }
            }
            RegCloseKey(hKey);
        }
    }
	return s_bHorizontalReading;
}

#endif

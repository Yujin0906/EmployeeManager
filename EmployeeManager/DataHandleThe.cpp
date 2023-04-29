// 스코프?
#include "DataHandle.h"

// 파일로부터 직원 정보를 읽어서 메모리에 저장한다.
ulong loadEmployee(EMPLOYEE** ppEmp)
{
	if (ppEmp == NULL)
		return 0;

	// 1. 파일의 사이즈를 알아야 함 (할당받은 메모리 크기를 결정) byte단위임!
	ulong lSize = getFileSize(EMPLOYEE_FILE);
	if (lSize == 0)
		return 0;

	// 2. 메모리를 할당 받음
	*ppEmp = (EMPLOYEE*)malloc(lSize);
	if (*ppEmp == NULL) // malloc가 성공했는지 체크
		return 0; // 리턴하면 실패했다는 뜻

	// 3. 파일을 메모리로 읽어옴
	ulong ret = ReadFromFile(EMPLOYEE_FILE, *ppEmp, lSize);
	if (ret == 0) // !ret와 ret == 0은 같은 뜻
	{
		if (*ppEmp)
		{
			free(*ppEmp);
			*ppEmp = NULL;
		}
	}

	return ret;
}


ulong loadBuseo(BUSEO** ppBuseo)
{
	if (ppBuseo == NULL)
		return 0;

	// 1. 파일의 사이즈를 알아야 함 (할당받은 메모리 크기를 결정) byte단위임!
	ulong lSize = getFileSize(BUSEO_FILE);
	if (lSize == 0)
		return 0;

	// 2. 메모리를 할당 받음
	*ppBuseo = (BUSEO*)malloc(lSize);
	if (*ppBuseo == NULL) // malloc가 성공했는지 체크
		return 0; // 리턴하면 실패했다는 뜻

	// 3. 파일을 메모리로 읽어옴
	ulong ret = ReadFromFile(BUSEO_FILE, *ppBuseo, lSize);
	if (ret == 0) // !ret와 ret == 0은 같은 뜻
	{
		if (*ppBuseo)
		{
			free(*ppBuseo);
			*ppBuseo = NULL;
		}
	}

	return ret;
}

ulong loadJikguep(JIKGUEP** ppJikguep)
{
	if (ppJikguep == NULL)
		return 0;

	// 1. 파일의 사이즈를 알아야 함 (할당받은 메모리 크기를 결정) byte단위임!
	ulong lSize = getFileSize(JIKGUEP_FILE);
	if (lSize == 0)
		return 0;

	// 2. 메모리를 할당 받음
	*ppJikguep = (JIKGUEP*)malloc(lSize);
	if (*ppJikguep == NULL) // malloc가 성공했는지 체크
		return 0; // 리턴하면 실패했다는 뜻

	// 3. 파일을 메모리로 읽어옴
	ulong ret = ReadFromFile(JIKGUEP_FILE, *ppJikguep, lSize);
	if (ret == 0) // !ret와 ret == 0은 같은 뜻
	{
		if (*ppJikguep)
		{
			free(*ppJikguep);
			*ppJikguep = NULL;
		}
	}

	return ret;
}

// 파일의 사이즈를 알 수 있는 함수
ulong getFileSize(const char* fileName)
{
	if (fileName == NULL)
		return 0;

	ulong pos = 0;
	FILE* fp = NULL;
	errno_t error = fopen_s(&fp, fileName, "r");	// 읽기 모드("r")일 경우에는 파일이 없으면 오픈 실패!(읽기 모드일 때만!! 다른 모드는 또 달라짐)
	if (error) // 파일 오픈에 실패한 경우
		return 0;

	// 파일 내에서 읽기, 쓰기 위치(파일 포지션)를 변경하는 함수
	// ex) fseek(fp, 0, SEEK_END); // position위치를 파일의 끝부분으로 이동시킨다는 의미
	// ex) fseek(fp, 0, SEEK_SET); // position위치를 파일의 첫부분으로 이동시킨다는 의미
	int ret = fseek(fp, 0, SEEK_END);
	if (ret == 0)
	{
		pos = (ulong)ftell(fp);
	}

	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}

	return pos;
}

ulong ReadFromFile(const char* fileName, void* pBuffer, ulong lSize)
{
	if (fileName == NULL || pBuffer == NULL || lSize == 0)
		return 0;

	ulong ret = 0;
	FILE* fp = NULL;
	errno_t error = fopen_s(&fp, fileName, "r+b");
	if (error) // 파일 오픈에 실패한 경우
		return 0;

	size_t result = fread(pBuffer, lSize, 1, fp);
	if (result)
	{
		ret = lSize;
	}

	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}

	return ret;
}

ulong WriteToFile(const char* fileName, void* pBuffer, ulong lSize)
{
	if (fileName == NULL || pBuffer == NULL || lSize == 0)
		return 0;

	ulong ret = 0;
	FILE* fp = NULL;
	errno_t error = fopen_s(&fp, fileName, "w+b"); // 쓰기 모드("w")일 경우에는 파일이 없으면 새로 생성!!!
	if (error) // 파일 오픈에 실패한 경우
		return 0;

	size_t result = fwrite(pBuffer, lSize, 1, fp);
	if (result)
	{
		ret = lSize;
	}

	if (fp)
	{
		fclose(fp);
		fp = NULL;
	}

	return ret;
}

/*
맨 처음 실행했을 때 데이터가 완전히 없을때도 아니면 데이터가 이미 존재하는 경우에도
사용 가능하도록 메모리에 데이터를 추가하는 기능까지 구현  */
ulong inputEmployee(EMPLOYEE** ppEmp, ulong lSize)
{
	if (ppEmp == NULL)
		return 0;

	// 화면을 클리어 하고
	system("cls");

	// 데이터를 입력받음
	EMPLOYEE emp;
	printf("사원 번호를 입력하세요 : ");
	scanf_s("%u", &emp.num);

	printf("사원명을 입력하세요 : ");
	scanf_s("%s", emp.name, MAX_NAME);

	printf("부서 코드를 입력하세요 : ");
	scanf_s("%u", &emp.buseo);

	printf("직급 코드를 입력하세요 : ");
	scanf_s("%u", &emp.jikguep);

	// 데이터가 이미 존재하는데 추가를 할 경우
	// 데이터 버퍼의 크기는 sizeof(EMPLOYEE)의 배수가 된다!
	ulong lNewSize = lSize + sizeof(EMPLOYEE);

	char* pBuffer = NULL;	// 임시적인 지역 포인터 변수
	pBuffer = (char*)malloc(lNewSize);
	if (pBuffer == NULL)	// malloc에 실패했으면 그냥 끝냄(리턴함)
		return 0;

	if (*ppEmp)
		// 메모리 복사
		memcpy(pBuffer, *ppEmp, lSize); // 새로 할당 받은 메모리에 원본(원래있던) 메모리 데이터를 카피한다.

	// 새로 입력 받은 데이터를 다시 복사한다.
	memcpy(pBuffer + lSize, &emp, sizeof(EMPLOYEE));

	if (*ppEmp)
	{
		free(*ppEmp);
		*ppEmp = NULL;
	}

	*ppEmp = (EMPLOYEE*)pBuffer; // 할당받은 주소 넘겨주기

	// 입력받은 데이터를 파일에 저장한다.

	WriteToFile(EMPLOYEE_FILE, pBuffer, lNewSize);

	return lNewSize;
}

ulong inputBuseo(BUSEO** ppBuseo, ulong lSize)
{
	if (ppBuseo == NULL)
		return 0;

	// 화면을 클리어 하고
	system("cls");

	// 데이터를 입력받음
	BUSEO buseo;
	printf("부서 번호를 입력하세요 : ");
	scanf_s("%u", &buseo.num);

	printf("부서명을 입력하세요 : ");
	scanf_s("%s", buseo.name, MAX_NAME);

	// 기존의 버퍼사이즈 + 새로 입력받은 버퍼의 사이즈 = 새로 할당 받을 버퍼의 사이즈
	ulong lNewSize = lSize + sizeof(BUSEO);
	char* pBuffer = NULL;
	pBuffer = (char*)malloc(lNewSize); // 새로운 버퍼 사이즈 만큼 힙 메모리 할당 시도
	if (pBuffer == NULL) // 힙 메모리의 버퍼를 할당받지 못했으면
		return 0;

	// 기본의 부서 정보가 있으면 새로 할당받은 버퍼에 먼저 카피를 하고
	if (*ppBuseo) // <- ppBuseo에 값이 있으면 이라는 뜻
		memcpy(pBuffer, *ppBuseo, lSize);

	// 새로 입력받은 데이터를 기존 데이터 뒤에 붙여 복사한다.
	memcpy(pBuffer + lSize, &buseo, sizeof(BUSEO));

	if (*ppBuseo)
	{
		free(*ppBuseo);
		*ppBuseo = NULL;
	}

	// 호출한 쪽에 새로 할당한 버퍼의 주소를 돌려준다. 
	*ppBuseo = (BUSEO*)pBuffer;

	WriteToFile(BUSEO_FILE, pBuffer, lNewSize);

	return lNewSize;
}

ulong inputJikguep(JIKGUEP** ppjikguep, ulong lSize)
{
	if (ppjikguep == NULL)
		return 0;

	// 화면을 클리어 하고
	system("cls");

	// 데이터를 입력받음
	JIKGUEP jikguep;
	printf("직급 코드를 입력하세요 : ");
	scanf_s("%u", &jikguep.num);

	printf("직급명을 입력하세요 : ");
	scanf_s("%s", jikguep.name, MAX_NAME);

	// 기존의 버퍼사이즈 + 새로 입력받은 버퍼의 사이즈 = 새로 할당 받을 버퍼의 사이즈
	ulong lNewSize = lSize + sizeof(JIKGUEP);
	char* pBuffer = NULL;
	pBuffer = (char*)malloc(lNewSize); // 새로운 버퍼 사이즈 만큼 힙 메모리 할당 시도
	if (pBuffer == NULL) // 힙 메모리의 버퍼를 할당받지 못했으면
		return 0;

	// 기본의 직급 정보가 있으면 새로 할당받은 버퍼에 먼저 카피를 하고
	if (*ppjikguep) // <- ppjikguep에 값이 있으면 이라는 뜻
		memcpy(pBuffer, *ppjikguep, lSize);

	// 새로 입력받은 데이터를 기존 데이터 뒤에 붙여 복사한다.
	memcpy(pBuffer + lSize, &jikguep, sizeof(JIKGUEP));

	if (*ppjikguep)
	{
		free(*ppjikguep);
		*ppjikguep = NULL;
	}

	// 호출한 쪽에 새로 할당한 버퍼의 주소를 돌려준다. 
	*ppjikguep = (JIKGUEP*)pBuffer;

	WriteToFile(JIKGUEP_FILE, pBuffer, lNewSize);

	return lNewSize;
}


void showEmployee(EMPLOYEE_DATA* pData)
{
	if (pData == NULL)
		return;

	system("cls");

	printf("사원번호 사원명  부서명  직급\n");
	printf("=============================\n");
	if (pData->pEmp == NULL)
	{
		printf("사원정보가 없습니다\n");
	}
	else
	{
		uint count = 0;
		count = pData->lEmpSize / sizeof(EMPLOYEE); // 내가 할당받은 EMPLOYEE_DATA 힙 버퍼의 사이즈를 바이트 단위로 바꾸는 것
		for (uint i = 0; i < count; i++)
		{
			printf("    %u\t", pData->pEmp[i].num);
			printf(" %s\t", pData->pEmp[i].name);
			char* buName = getBuseoName(pData->pBuseo, pData->lBuseoSize, pData->pEmp[i].buseo);
			(buName == NULL) ? printf("%u\t", pData->pEmp[i].buseo) : printf(" %s\t", buName);
			char* jikName = getJikguepName(pData->pJikguep, pData->lJikguepSize, pData->pEmp[i].jikguep);
			(buName == NULL) ? printf("%u\t", pData->pEmp[i].jikguep) : printf(" %s\t\n", jikName);

		}
	}
}

void showBuseo(BUSEO* pBuseo, ulong lSize)
{
	if (pBuseo == NULL)
		return;

	system("cls");

	printf("부서코드\t부서명\n");
	printf("======================\n");
	if (pBuseo == NULL)
	{
		printf("부서정보가 없습니다\n");
	}
	else
	{
		uint count = 0;
		count = lSize / sizeof(BUSEO);
		for (uint i = 0; i < count; i++)
		{
			printf("%u\t", pBuseo[i].num);
			printf("%s\n", pBuseo[i].name);
		}
	}
}

void showJikguep(JIKGUEP* pjikguep, ulong lSize)
{
	if (pjikguep == NULL)
		return;

	system("cls");

	printf("직급코드\t직급명\n");
	printf("======================\n");
	if (pjikguep == NULL)
	{
		printf("직급정보가 없습니다\n");
	}
	else
	{
		uint count = 0;
		count = lSize / sizeof(JIKGUEP);
		for (uint i = 0; i < count; i++)
		{
			printf("%u\t", pjikguep[i].num);
			printf("%s\n", pjikguep[i].name);
		}
	}
}

void showMenu()
{
	system("cls");

	printf("1. 직원 정보 보기\n");
	printf("2. 직원 정보 입력\n");
	printf("3. 직원 정보 수정\n");
	printf("4. 직원 정보 삭제\n");
	printf("=================\n"); \
		printf("5. 부서 정보 보기\n");
	printf("6. 부서 정보 입력\n");
	printf("7. 부서 정보 수정\n");
	printf("8. 부서 정보 삭제\n");
	printf("=================\n"); \
		printf("9. 직급 정보 보기\n");
	printf("0. 직급 정보 입력\n");
	printf("a. 직급 정보 수정\n");
	printf("b. 직급 정보 삭제\n");

}

void showSubMenu()
{
	printf("\n");
	printf("메뉴보기(m)\n");

	int ch = _getch();
	switch (ch)
	{
	case 'm':
	case 'M':
		return;
	}
}

char* getBuseoName(BUSEO* pBuseo, ulong lsize, uint code)
{
	if (pBuseo == NULL || lsize == 0)
		return NULL;

	uint count = lsize / sizeof(BUSEO);
	for (uint i = 0; i < count; i++)
	{
		if (pBuseo[i].num == code)
			return pBuseo[i].name;
	}
}

char* getJikguepName(JIKGUEP* pJikguep, ulong lsize, uint code)
{
	if (pJikguep == NULL || lsize == 0)
		return NULL;

	uint count = lsize / sizeof(JIKGUEP);
	for (uint i = 0; i < count; i++)
	{
		if (pJikguep[i].num == code)
			return pJikguep[i].name;
	}
}
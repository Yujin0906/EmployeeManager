#pragma once // <- 이거는 cpp에서만 가능

/*
#ifndef __DATA_HANDLE_H_____20230330_86745123___
#define __DATA_HANDLE_H_____20230330_86745123___

#endif
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // _getch()
#include <string.h>

typedef unsigned char			byte;
typedef unsigned int			uint;
typedef unsigned long			ulong;

#define MAX_NAME				20
#define EMPLOYEE_FILE			"employee.dat"
#define BUSEO_FILE				"buseo.dat"
#define JIKGUEP_FILE			"jikguep.dat"

#define SHOW_EMPLOYEE '1'
#define INSERT_EMPLOYEE '2'
#define UPDATE_EMPLOYEE '3'
#define DELETC_EMPLOYEE '4'

#define SHOW_BUSEO '5'
#define INSERT_BUSEO '6'
#define UPDATE_BUSEO '7'
#define DELETC_BUSEO '8'

#define SHOW_JIKGUEP '9'
#define INSERT_JIKGUEP '0'
#define UPDATE_JIKGUEP 'a'
#define DELETC_JIKGUEP 'b'

// 직원 정보
typedef struct _EMPLOYEE {
	uint	num = 0;			// 사번
	char	name[MAX_NAME] = { 0 };	// 사원 이름
	uint	buseo = 0;			// 부서 코드
	uint	jikguep = 0;		// 직급 코드
} EMPLOYEE;

// 부서 정보
typedef struct _BUSEO {
	uint	num = 0;
	char	name[MAX_NAME] = { 0 };
	// ...
} BUSEO;

// 직급 정보
typedef struct _JIKGUEP {
	uint	num = 0;
	char name[MAX_NAME] = { 0 };
} JIKGUEP;

// 통합 정보 -> 힙에 관리를 함
typedef struct _EMPLOYEE_DATA {
	EMPLOYEE* pEmp = NULL;	// 각 데이터들의 포인터
	ulong		lEmpSize = 0;	// 할당받은 데이터 버퍼의 사이즈(byte 단위)

	BUSEO* pBuseo = NULL;
	ulong		lBuseoSize = 0;

	JIKGUEP* pJikguep = NULL;
	ulong		lJikguepSize = 0;

} EMPLOYEE_DATA;

void showMenu();
void showSubMenu();

void showEmployee(EMPLOYEE_DATA* pData);
void showBuseo(BUSEO* pBuseo, ulong lSize);
void showJikguep(JIKGUEP* pjikguep, ulong lSize);

ulong loadEmployee(EMPLOYEE** ppEmp);
ulong loadBuseo(BUSEO** ppBuseo);
ulong loadJikguep(JIKGUEP** ppJikguep); ulong getFileSize(const char* fileName);

ulong ReadFromFile(const char* fileName, void* pBuffer, ulong lSize);
ulong WriteToFile(const char* fileName, void* pBuffer, ulong lSize);

ulong inputEmployee(EMPLOYEE** ppEmp, ulong lSize);
ulong inputBuseo(BUSEO** ppBuseo, ulong lSize);
ulong inputJikguep(JIKGUEP** ppjikguep, ulong lSize);

char* getBuseoName(BUSEO* pBuseo, ulong lsize, uint code);
char* getJikguepName(JIKGUEP* pJikguep, ulong lsize, uint code);
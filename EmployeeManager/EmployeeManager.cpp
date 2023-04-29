// 초 심플한 인사관리 프로그램
// 
// 직원관리, 직급관리, 부서관리
// 관계형 데이터베이스와 유사하게 파일을 가지고 만들어봄!!!

// CRUD
// Create : 데이터 생성 및 저장
// Read : 로드
// Update : 데이터 수정
// Delete : 데이터 삭제

#include "DataHandle.h"

int main()
{
	EMPLOYEE_DATA	data;
	memset(&data, 0, sizeof(EMPLOYEE_DATA));

	// 초기화 작업
	// 파일에서 각 데이터들을 로딩(Heap 영역)한다!!!
	data.lEmpSize = loadEmployee(&data.pEmp); // 포인터 변수 data.pEmp의 주소를 넘겨줌, 사원정보 로딩
	data.lBuseoSize = loadBuseo(&data.pBuseo); // 부서정보 로딩
	data.lJikguepSize = loadJikguep(&data.pJikguep); // 직급정보 로딩

	// 기능들을 수행
	showMenu();

	while (1)
	{
		int ch = _getch();
		if (ch == 'x' || ch == 'X') // 사용자가 x키를 눌렀을 때는 루프를 탈출함 종료
			break;
		switch (ch)
		{
		case SHOW_EMPLOYEE:
			showEmployee(&data);
			showSubMenu();
			break;

		case INSERT_EMPLOYEE:
			data.lEmpSize = inputEmployee(&data.pEmp, data.lEmpSize);
			showEmployee(&data);
			showSubMenu();
			break;

		case UPDATE_EMPLOYEE:
			break;

		case DELETC_EMPLOYEE:
			break;

		case SHOW_BUSEO:
			showBuseo(data.pBuseo, data.lBuseoSize);
			showSubMenu(); // showSubMenu의 목적 : 화면이 안 넘어가게 사용자의 키 입력을 기다림
			break;

		case INSERT_BUSEO:
			data.lBuseoSize = inputBuseo(&data.pBuseo, data.lBuseoSize);
			showBuseo(data.pBuseo, data.lBuseoSize);
			showSubMenu();
			break;

		case UPDATE_BUSEO:
			break;

		case DELETC_BUSEO:
			break;

		case SHOW_JIKGUEP:
			showJikguep(data.pJikguep, data.lJikguepSize);
			showSubMenu();
			break;

		case INSERT_JIKGUEP:
			data.lJikguepSize = inputJikguep(&data.pJikguep, data.lJikguepSize);
			showJikguep(data.pJikguep, data.lJikguepSize);
			showSubMenu();
			break;

		case UPDATE_JIKGUEP:
			break;

		case DELETC_JIKGUEP:
			break;
		}

		showMenu();
	}
	// 1. 키보드로부터 데이터를 입력받아서

	if (data.pEmp)
	{
		free(data.pEmp);
		data.pEmp = NULL;
	}

	if (data.pBuseo)
	{
		free(data.pBuseo);
		data.pBuseo = NULL;
	}

	if (data.pJikguep)
	{
		free(data.pJikguep);
		data.pJikguep = NULL;
	}

	return 0;
}

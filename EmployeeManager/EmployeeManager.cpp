// �� ������ �λ���� ���α׷�
// 
// ��������, ���ް���, �μ�����
// ������ �����ͺ��̽��� �����ϰ� ������ ������ ����!!!

// CRUD
// Create : ������ ���� �� ����
// Read : �ε�
// Update : ������ ����
// Delete : ������ ����

#include "DataHandle.h"

int main()
{
	EMPLOYEE_DATA	data;
	memset(&data, 0, sizeof(EMPLOYEE_DATA));

	// �ʱ�ȭ �۾�
	// ���Ͽ��� �� �����͵��� �ε�(Heap ����)�Ѵ�!!!
	data.lEmpSize = loadEmployee(&data.pEmp); // ������ ���� data.pEmp�� �ּҸ� �Ѱ���, ������� �ε�
	data.lBuseoSize = loadBuseo(&data.pBuseo); // �μ����� �ε�
	data.lJikguepSize = loadJikguep(&data.pJikguep); // �������� �ε�

	// ��ɵ��� ����
	showMenu();

	while (1)
	{
		int ch = _getch();
		if (ch == 'x' || ch == 'X') // ����ڰ� xŰ�� ������ ���� ������ Ż���� ����
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
			showSubMenu(); // showSubMenu�� ���� : ȭ���� �� �Ѿ�� ������� Ű �Է��� ��ٸ�
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
	// 1. Ű����κ��� �����͸� �Է¹޾Ƽ�

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

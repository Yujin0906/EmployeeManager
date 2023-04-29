// ������?
#include "DataHandle.h"

// ���Ϸκ��� ���� ������ �о �޸𸮿� �����Ѵ�.
ulong loadEmployee(EMPLOYEE** ppEmp)
{
	if (ppEmp == NULL)
		return 0;

	// 1. ������ ����� �˾ƾ� �� (�Ҵ���� �޸� ũ�⸦ ����) byte������!
	ulong lSize = getFileSize(EMPLOYEE_FILE);
	if (lSize == 0)
		return 0;

	// 2. �޸𸮸� �Ҵ� ����
	*ppEmp = (EMPLOYEE*)malloc(lSize);
	if (*ppEmp == NULL) // malloc�� �����ߴ��� üũ
		return 0; // �����ϸ� �����ߴٴ� ��

	// 3. ������ �޸𸮷� �о��
	ulong ret = ReadFromFile(EMPLOYEE_FILE, *ppEmp, lSize);
	if (ret == 0) // !ret�� ret == 0�� ���� ��
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

	// 1. ������ ����� �˾ƾ� �� (�Ҵ���� �޸� ũ�⸦ ����) byte������!
	ulong lSize = getFileSize(BUSEO_FILE);
	if (lSize == 0)
		return 0;

	// 2. �޸𸮸� �Ҵ� ����
	*ppBuseo = (BUSEO*)malloc(lSize);
	if (*ppBuseo == NULL) // malloc�� �����ߴ��� üũ
		return 0; // �����ϸ� �����ߴٴ� ��

	// 3. ������ �޸𸮷� �о��
	ulong ret = ReadFromFile(BUSEO_FILE, *ppBuseo, lSize);
	if (ret == 0) // !ret�� ret == 0�� ���� ��
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

	// 1. ������ ����� �˾ƾ� �� (�Ҵ���� �޸� ũ�⸦ ����) byte������!
	ulong lSize = getFileSize(JIKGUEP_FILE);
	if (lSize == 0)
		return 0;

	// 2. �޸𸮸� �Ҵ� ����
	*ppJikguep = (JIKGUEP*)malloc(lSize);
	if (*ppJikguep == NULL) // malloc�� �����ߴ��� üũ
		return 0; // �����ϸ� �����ߴٴ� ��

	// 3. ������ �޸𸮷� �о��
	ulong ret = ReadFromFile(JIKGUEP_FILE, *ppJikguep, lSize);
	if (ret == 0) // !ret�� ret == 0�� ���� ��
	{
		if (*ppJikguep)
		{
			free(*ppJikguep);
			*ppJikguep = NULL;
		}
	}

	return ret;
}

// ������ ����� �� �� �ִ� �Լ�
ulong getFileSize(const char* fileName)
{
	if (fileName == NULL)
		return 0;

	ulong pos = 0;
	FILE* fp = NULL;
	errno_t error = fopen_s(&fp, fileName, "r");	// �б� ���("r")�� ��쿡�� ������ ������ ���� ����!(�б� ����� ����!! �ٸ� ���� �� �޶���)
	if (error) // ���� ���¿� ������ ���
		return 0;

	// ���� ������ �б�, ���� ��ġ(���� ������)�� �����ϴ� �Լ�
	// ex) fseek(fp, 0, SEEK_END); // position��ġ�� ������ ���κ����� �̵���Ų�ٴ� �ǹ�
	// ex) fseek(fp, 0, SEEK_SET); // position��ġ�� ������ ù�κ����� �̵���Ų�ٴ� �ǹ�
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
	if (error) // ���� ���¿� ������ ���
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
	errno_t error = fopen_s(&fp, fileName, "w+b"); // ���� ���("w")�� ��쿡�� ������ ������ ���� ����!!!
	if (error) // ���� ���¿� ������ ���
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
�� ó�� �������� �� �����Ͱ� ������ �������� �ƴϸ� �����Ͱ� �̹� �����ϴ� ��쿡��
��� �����ϵ��� �޸𸮿� �����͸� �߰��ϴ� ��ɱ��� ����  */
ulong inputEmployee(EMPLOYEE** ppEmp, ulong lSize)
{
	if (ppEmp == NULL)
		return 0;

	// ȭ���� Ŭ���� �ϰ�
	system("cls");

	// �����͸� �Է¹���
	EMPLOYEE emp;
	printf("��� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%u", &emp.num);

	printf("������� �Է��ϼ��� : ");
	scanf_s("%s", emp.name, MAX_NAME);

	printf("�μ� �ڵ带 �Է��ϼ��� : ");
	scanf_s("%u", &emp.buseo);

	printf("���� �ڵ带 �Է��ϼ��� : ");
	scanf_s("%u", &emp.jikguep);

	// �����Ͱ� �̹� �����ϴµ� �߰��� �� ���
	// ������ ������ ũ��� sizeof(EMPLOYEE)�� ����� �ȴ�!
	ulong lNewSize = lSize + sizeof(EMPLOYEE);

	char* pBuffer = NULL;	// �ӽ����� ���� ������ ����
	pBuffer = (char*)malloc(lNewSize);
	if (pBuffer == NULL)	// malloc�� ���������� �׳� ����(������)
		return 0;

	if (*ppEmp)
		// �޸� ����
		memcpy(pBuffer, *ppEmp, lSize); // ���� �Ҵ� ���� �޸𸮿� ����(�����ִ�) �޸� �����͸� ī���Ѵ�.

	// ���� �Է� ���� �����͸� �ٽ� �����Ѵ�.
	memcpy(pBuffer + lSize, &emp, sizeof(EMPLOYEE));

	if (*ppEmp)
	{
		free(*ppEmp);
		*ppEmp = NULL;
	}

	*ppEmp = (EMPLOYEE*)pBuffer; // �Ҵ���� �ּ� �Ѱ��ֱ�

	// �Է¹��� �����͸� ���Ͽ� �����Ѵ�.

	WriteToFile(EMPLOYEE_FILE, pBuffer, lNewSize);

	return lNewSize;
}

ulong inputBuseo(BUSEO** ppBuseo, ulong lSize)
{
	if (ppBuseo == NULL)
		return 0;

	// ȭ���� Ŭ���� �ϰ�
	system("cls");

	// �����͸� �Է¹���
	BUSEO buseo;
	printf("�μ� ��ȣ�� �Է��ϼ��� : ");
	scanf_s("%u", &buseo.num);

	printf("�μ����� �Է��ϼ��� : ");
	scanf_s("%s", buseo.name, MAX_NAME);

	// ������ ���ۻ����� + ���� �Է¹��� ������ ������ = ���� �Ҵ� ���� ������ ������
	ulong lNewSize = lSize + sizeof(BUSEO);
	char* pBuffer = NULL;
	pBuffer = (char*)malloc(lNewSize); // ���ο� ���� ������ ��ŭ �� �޸� �Ҵ� �õ�
	if (pBuffer == NULL) // �� �޸��� ���۸� �Ҵ���� ��������
		return 0;

	// �⺻�� �μ� ������ ������ ���� �Ҵ���� ���ۿ� ���� ī�Ǹ� �ϰ�
	if (*ppBuseo) // <- ppBuseo�� ���� ������ �̶�� ��
		memcpy(pBuffer, *ppBuseo, lSize);

	// ���� �Է¹��� �����͸� ���� ������ �ڿ� �ٿ� �����Ѵ�.
	memcpy(pBuffer + lSize, &buseo, sizeof(BUSEO));

	if (*ppBuseo)
	{
		free(*ppBuseo);
		*ppBuseo = NULL;
	}

	// ȣ���� �ʿ� ���� �Ҵ��� ������ �ּҸ� �����ش�. 
	*ppBuseo = (BUSEO*)pBuffer;

	WriteToFile(BUSEO_FILE, pBuffer, lNewSize);

	return lNewSize;
}

ulong inputJikguep(JIKGUEP** ppjikguep, ulong lSize)
{
	if (ppjikguep == NULL)
		return 0;

	// ȭ���� Ŭ���� �ϰ�
	system("cls");

	// �����͸� �Է¹���
	JIKGUEP jikguep;
	printf("���� �ڵ带 �Է��ϼ��� : ");
	scanf_s("%u", &jikguep.num);

	printf("���޸��� �Է��ϼ��� : ");
	scanf_s("%s", jikguep.name, MAX_NAME);

	// ������ ���ۻ����� + ���� �Է¹��� ������ ������ = ���� �Ҵ� ���� ������ ������
	ulong lNewSize = lSize + sizeof(JIKGUEP);
	char* pBuffer = NULL;
	pBuffer = (char*)malloc(lNewSize); // ���ο� ���� ������ ��ŭ �� �޸� �Ҵ� �õ�
	if (pBuffer == NULL) // �� �޸��� ���۸� �Ҵ���� ��������
		return 0;

	// �⺻�� ���� ������ ������ ���� �Ҵ���� ���ۿ� ���� ī�Ǹ� �ϰ�
	if (*ppjikguep) // <- ppjikguep�� ���� ������ �̶�� ��
		memcpy(pBuffer, *ppjikguep, lSize);

	// ���� �Է¹��� �����͸� ���� ������ �ڿ� �ٿ� �����Ѵ�.
	memcpy(pBuffer + lSize, &jikguep, sizeof(JIKGUEP));

	if (*ppjikguep)
	{
		free(*ppjikguep);
		*ppjikguep = NULL;
	}

	// ȣ���� �ʿ� ���� �Ҵ��� ������ �ּҸ� �����ش�. 
	*ppjikguep = (JIKGUEP*)pBuffer;

	WriteToFile(JIKGUEP_FILE, pBuffer, lNewSize);

	return lNewSize;
}


void showEmployee(EMPLOYEE_DATA* pData)
{
	if (pData == NULL)
		return;

	system("cls");

	printf("�����ȣ �����  �μ���  ����\n");
	printf("=============================\n");
	if (pData->pEmp == NULL)
	{
		printf("��������� �����ϴ�\n");
	}
	else
	{
		uint count = 0;
		count = pData->lEmpSize / sizeof(EMPLOYEE); // ���� �Ҵ���� EMPLOYEE_DATA �� ������ ����� ����Ʈ ������ �ٲٴ� ��
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

	printf("�μ��ڵ�\t�μ���\n");
	printf("======================\n");
	if (pBuseo == NULL)
	{
		printf("�μ������� �����ϴ�\n");
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

	printf("�����ڵ�\t���޸�\n");
	printf("======================\n");
	if (pjikguep == NULL)
	{
		printf("���������� �����ϴ�\n");
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

	printf("1. ���� ���� ����\n");
	printf("2. ���� ���� �Է�\n");
	printf("3. ���� ���� ����\n");
	printf("4. ���� ���� ����\n");
	printf("=================\n"); \
		printf("5. �μ� ���� ����\n");
	printf("6. �μ� ���� �Է�\n");
	printf("7. �μ� ���� ����\n");
	printf("8. �μ� ���� ����\n");
	printf("=================\n"); \
		printf("9. ���� ���� ����\n");
	printf("0. ���� ���� �Է�\n");
	printf("a. ���� ���� ����\n");
	printf("b. ���� ���� ����\n");

}

void showSubMenu()
{
	printf("\n");
	printf("�޴�����(m)\n");

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
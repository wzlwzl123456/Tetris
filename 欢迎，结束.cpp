void Game::Welcome()
{
	settextcolor(WHITE);
	settextstyle(60, 0, _T("����"));
	outtextxy(440, 200, "����˹����");
	settextstyle(30, 0, "����");
	outtextxy(200, 300, "����˹�����Ƕ���˹����ĸĽ���");
	outtextxy(200, 400, "��һ�������ȥһ�У��ͻ�����һ�����������������һ��");
	outtextxy(400, 500, "����ո�ʼ������e�˳�");
	char input;
	input = getch();
	if (input == ' ')
	{
		return 0;
	}
	if (input == 'e')
	{
		exit(0);
	}
}
void Game::GameOver()
{
	settextcolor(WHITE);
	sttextstyle(60, 0, _T("����"));
	outtextxy(440, 200, "GameOver");
	if (P2_map.gettop())
	{
		outtextxy(500, 300, "P1win!");
	}
	else {
		outtextxy(500, 300, "P2win!");
	}
	outtextxy(400, 500, "����ո����������e�˳�");
	char input;
	input = getch();
	if (input == ' ')
	{
		return 0;
	}
	if (input == 'e')
	{
		exit(0);
	}
}
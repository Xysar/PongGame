#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input->buttons[b].changed)

float player1P, player1V;

float player2P, player2V;

float ballXP = 0, ballXV = 75, ballXA = 0.f;
float ballYP = 0, ballYV = 0.f, ballYA = 0.f;

float ballHalfSize = 1;

float arenaHalfSize = 45;
float player1HalfSizey = 12, player1HalfSizex = 2.5;
float player2HalfSizey = 12, player2HalfSizex = 2.5;

void simulateGame(Input* input, float dt){
	clear_screen(0xff5500);
	drawRect(0, 0, 85, arenaHalfSize, 0xffaa33);

	float player1A = 0.f;
	if (is_down(BUTTON_UP)) player1A += 2000;
	if (is_down(BUTTON_DOWN)) player1A -= 2000;

	float player2A = 0.f;
	if (is_down(BUTTON_W)) player2A += 2000;
	if (is_down(BUTTON_S)) player2A -= 2000;
	if (ballYV > 100)
		ballYV = 100;
	if (ballYV < -100)
		ballYV = -100;
	if (ballXV > 150)
		ballXV = 150;
	if (ballXV < -150)
		ballXV = -150;
	player1A -= player1V * 10.f;
	player1P = player1P + player1V * dt + ((player1A * dt * dt) / 2);
	player1V = player1V + player1A * dt;

	player2A -= player2V * 10.f;
	player2V = player2V + player2A * dt;
	player2P = player2P + player2V * dt + ((player2A * dt * dt) / 2);

	//ballXV = ballXV + ballXA * dt;
	ballXP = ballXP + ballXV * dt + ((ballXA * dt * dt) / 2);

   // ballYV = ballYV + ballYA * dt;
	ballYP = ballYP + ballYV * dt + ((ballYA * dt * dt) / 2);

	if (player1P + player1HalfSizey > arenaHalfSize) {
		player1P = arenaHalfSize - player1HalfSizey;
		player1V = 0;
	}
	if (-(player1P - player1HalfSizey) > arenaHalfSize) {
		player1P = -arenaHalfSize + player1HalfSizey;
		player1V = 0;
	}

	if (player2P + player2HalfSizey > arenaHalfSize) {
		player2P = arenaHalfSize - player2HalfSizey;
		player2V = 0;
	}
	if (-(player2P - player2HalfSizey) > arenaHalfSize) {
		player2P = -arenaHalfSize + player2HalfSizey;
		player2V = 0;
	}

	if (-(ballYP - ballHalfSize) > arenaHalfSize) {
		ballYP = -arenaHalfSize + ballHalfSize;
		ballYV = -ballYV;
	}
	if ((ballYP + ballHalfSize) > arenaHalfSize) {
		ballYP = arenaHalfSize - ballHalfSize;
		ballYV = -ballYV;
	}

	if ((ballXP + ballHalfSize > 80 - player1HalfSizex) && (ballXP < 80 + player1HalfSizex)&& (ballYP < player1P + player1HalfSizey + ballHalfSize) && (ballYP > player1P - player1HalfSizey - ballHalfSize)){
		float curve = ballYP - player1P; 
		ballYV += curve * 3;
		ballYV += player1V /2;
		ballXP = 80 - player1HalfSizex - 1;
		ballXV = -ballXV - 5;
	}

	if ((ballXP - ballHalfSize < -80 + player2HalfSizex) && (ballXP > -80 - player2HalfSizex) && (ballYP < player2P + player2HalfSizey + ballHalfSize) && (ballYP > player2P - player2HalfSizey - ballHalfSize)){
		float curve = ballYP - player2P;
		ballYV += curve * 3;
		ballYV += player2V / 2;
		ballXP = -79 + player2HalfSizex;
		ballXV = -ballXV +5;
	}

	if (ballXP > 85 || ballXP < -85) {
		ballXP = 0;
		ballYP = 0;
		ballXV = ballXV < 0 ? 75 : -75;
		ballYV = 0;
	}

	drawRect(-80, player2P, player2HalfSizex, player2HalfSizey, 0xff0000); //player 2
	drawRect(80, player1P, player1HalfSizex, player1HalfSizey, 0xff0000); //player 1
	drawRect(ballXP, ballYP, ballHalfSize, ballHalfSize, 0xffffff);
}
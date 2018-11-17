#GameGlass.cpp(.h)
게임 진행관련 파일

#OpenGl_Test.cpp
OpenGL 게임화면 출력관련 파일.

#vshader_a9.glsl
VertexShader 파일

#fshader_a9.glsl
FragmentShader 파일

#game_map.csv
50x50 크기의 map정보를 나타내는 파일.

아래와 같이 구분
blank=0;
wall=1;
player=2;
enemy=3;
item01=4;
item02=5;

#game_map_easy.csv
조교님의 테스트 편의를 위한 map모델.
시작 시 보이는 적 3명 제거시 승리.

#이외의 소스, 헤더파일
https://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/
위의 링크에서 교과서 제공 헤더파일 사용. (벡터연산, 매트릭스 연산, shader 초기화, 계층구조 예제 등)
========================================
#키설명
이동: 방향키
공격: 스페이스바
재시작: 'R' or 'r'

#게임 설명
1. 시간제한 100초
2. 승리조건: 적 몰살
3. LIFE==0 일때 죽음
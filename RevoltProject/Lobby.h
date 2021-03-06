#pragma once

class UIObject;					// UI오브젝트를 사용하기 위한 전방선언 클래스
class MtlTex;					// 재질을 사용하기 위한 전방선언 클래스
class Camera;					// 카메라 클래스를 사용하기 위한 전방선언 클래스
class Thing;					// 오브젝트 클래스
class SelectMap;				// SelectMap Class

class ProfileList;
class Map;

/*   로비 UI 클래스   */
class cCreateProfile;			// 유저 파일 만들기 클래스
class cNetworkLobby;			// 멀티플레이어 로비 상태
//class InGameUI;					// InGameUI
class cSelectCarLob;			// 자동차 선택UI클래스
class cViewCarLob;				// 자동차 보여주는 
class cNetworkInRoom;			// 방 클래스
//===================================================================
// - written by 김선호
// - 로비 창 구현
// - 로비 구현 할 때 이 클래스 내부에서만 처리할 것
//===================================================================

//===================================================================
// - written by 김선호
// - @@ 텍스트 인덱스의 갯수가 4개이면 처음시작은 0부터 시작하고 끝은 3이다.
//===================================================================

struct ST_Object
{
	LOBBY*				m_pNextLob;					// 엔터키를 눌렀을 때 다음 로비상태
	LOBBY				m_prevLob;					// ESC키를 눌렀을 때 이전 로비상태
	float				m_time;						// 화면을 바꿀 시간
	int					m_count;					// 메뉴 텍스트 위아래 인덱스의 사이즈 
	int					m_selectCnt;				// 메뉴 오른쪽 왼쪽 인덱스 사이즈

	D3DXVECTOR3			m_target;					// 카메라 방향
	UIObject*			m_pObject;					// 해당 UI Object
	D3DXVECTOR3			m_camLookAt;				// Camera LookAt

	ST_Object()
	{
		m_time = 0.0f;
		m_count = 0;
		m_target = D3DXVECTOR3(0, 0, 0);
		m_camLookAt = D3DXVECTOR3(0, 0, 0);
	}
};

class Lobby
{
protected:
	std::map<LOBBY, ST_Object*>	m_mapLobby;		// UI 이미지들을 저장하는 map STL
	LPD3DXSPRITE				m_pSprite;		// UI 이미지를 출력하는 sprite변수

	LPD3DXMESH					m_pObjMesh;		// 로비 오브젝트를 그리기 위한 Mesh 변수
	std::vector<MtlTex*>		m_vecObjMtlTex;	// 오브젝트의 매터리얼를 저장하는 변수

	LOBBY	m_stateLobby;						// 로비 상태 를 저장하는 변수
	MAP_TYPE m_stateMapType;
	float	m_time;								// 변경 시간을 나타내는 타임 변수
	int		m_select;							// 현재 위아래 커서의 위치
	int		m_leftAndrightSelect;				// 현재 오른쪽 왼쪽 커서의 위치;

	float m_CamLerpSpd;
	D3DXVECTOR3 m_vCamPos;
	D3DXVECTOR3 m_vLookAt;

	//===================================================================
	// - written by 윤동훈
	// - 맵 선택
	// - 로비 구현 할 때 이 클래스 내부에서만 처리할 것
	//===================================================================

	SelectMap*			m_pSelectMap;			// Select Map Class
	//InGameUI*			m_pInGameUI;			// InGame UI;

	//===================================================================
	// - written by 정종훈
	// - 프로필 Load/Save작업
	// - 로비 구현 할 때 이 클래스 내부에서만 처리할 것
	//===================================================================
	std::vector<std::string> m_vProfileList;	// 프로필 목록
	std::string				 m_PlayerName;		// 선택된 이름

	ProfileList*		 	 m_pfileList;		// 프로필 리스트
	Map*					 m_pMap;
	std::vector<std::string> m_vecMapName;


	//===================================================================
	// - written by 김선호
	// - 멀티 플레이 작업
	// - 멀티 맵 로비 구현
	//===================================================================
	cNetworkLobby*		m_multiLobby;				// 멀티 로비 생성
	cCreateProfile*		m_pCreateProfileLobby;		// 사용자 생성 로비 클래스
	cSelectCarLob*		m_pSelectCarLobbby;			// 자동차 생성 로비 클래스
	cViewCarLob*		m_pViewCarLobby;			// 자동차 뷰어 로비 클래스
	cNetworkInRoom*		m_pInRoom;					// 멀티 방 클래스

public:
	Lobby();
	~Lobby();

	/*   기본적인 루프 메서드   */
	void Setup();					// 초기화 작업 메서드
	void Update();					// 동기화 작업할 메서드
	void Render();					// 실질적으로 그릴 메서드
	void Destroy();					// 제거 메서드 - 태섭

	/*   클래스 안에 사용할 루프 메서드   */
	void KeyUpdate();				// 키 이벤트 발생 갱신 메서드
	void TimeUpdate();				// 시간이 흐를 때 마다 발생 하는 이벤트를 갱신하는 메서드
	void SetUpUI();					// UI 셋업작업

	D3DXVECTOR3 GetTarget() { return m_mapLobby[m_stateLobby]->m_target; }		// 카메라가 보는 방향을 반환해주는 메서드


	void LinkMap(Map* map) { m_pMap = map; }
};


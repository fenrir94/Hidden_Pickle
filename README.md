
# 게임 개발 마일스톤 플랜 & 게임 문서

### Development Plan

| 마일스톤 | 주차 | 기간 | 목표 | 주요 작업 | 비고 |
|----------|------|-------|-------|------------|------|
| 개발 | 1주차 | 04-10 ~ 04-18 | 핵심 루프 & 아이템 구현 | - 캐릭터 설계<br>- 기본 플레이 흐름 구축<br>- 충돌 알고리즘<br>- 아이템 객체<br>- 아이템 획득 |  |
| 개발 | 2주차 | 04-19 ~ 04-25 | 적 AI<br> 미니맵 구현<br> 총 구현 | - 적 AI 구현<br>- 미니맵 적용<br>- 미니맵 내 아이콘 표시<br>- 사격 시스템 구현 |  |
| 폴리싱 | 3주차 | 04-26 ~ 05-02 | 전투 연출 | - 전투 이펙트 / 피격 연출 |  |
| 폴리싱 | 4주차 | 05-03 ~ 05-09 | UX 개선 + 튜토리얼 도입 | - 간단 튜토리얼<br>- 행동 제한 UI 안내<br>- 흐름 정리 |  |
| 빌드 안정화 | 5주차 | 05-10 ~ 05-15 | 최종 디버깅 & 밸런스 조정 | - 리그레션 테스트<br>- 유닛/시너지 수치 조정<br>- 최종 배포용 빌드 |  |

---

### Specification 링크 

> https://docs.google.com/document/d/1LiNeQ1GpmIdh1t7xW8zuEeDH3ThrzKeU8S-wNIEiOQQ/edit?usp=sharing

---

### Daily Report 링크

> https://docs.google.com/spreadsheets/d/13Tnr1Tp5oYZKaIVBKdh3jvO0Z7FrRE0TroR3LHVl-EU/edit?usp=sharing

---

### 게임 한 줄 소개

**보이지 않는 적을 피해 탈출하는 생존 어드벤쳐 게임입니다.**

---

### 게임 목표 / 승리 조건

- 열쇠를 획득하고 탈출 지점에 도달하면 승리
- 적에게 공격 받거나 충돌하여 체력이 0이 되면 패배

---

### 주요 게임 오브젝트

- 플레이어 (체력, 좌표)
- 적 NPC (공격력, 체력, 좌표)
- 적 NPC 발자국(생성 시간)
- (미구현)미니맵(탈출지점, 아이템 상자)
- 방해물(충돌시 플레이어에게 적용되는 효과)
- 아이템 & 아이템 상자(아이템 획득시 캐릭터 추가 기능, 상자 내 아이템)

---

### 게임 UI/UX 구성

- 플레이어 정보: HP, 보유 아이템
- 상호작용: 아이템 획득, 탈출
- 상태 표시: 보유 아이템 및 아이템 자원(ex. 배터리, 탄약) 표시
- 미니맵: 탈출지점, 아이템 상자

---

### 게임 흐름

> 메인 화면 > 스테이지 진행 

1. 스테이지 입장  
2. 발자국을 보면서 적을 피해 맵 탐색
3. 맵에 배치된 아이템 상자에서 열쇠 획득
4. 열쇠를 가지고 탈출 지점에 도착하면 승리

---

### 플레이어 행동 / 선택 / 영향

- wasd, 방향키: 상하좌우 이동
- 스페이스 바: 랜턴 사용 (빛 발생)
- 아이템 획득
- (미구현)엄폐물에 숨기
- (미구현)총기 발포 (소리 발생)

---

### 플레이 영상
 - [1주차 영상](https://drive.google.com/file/d/1BqVm4FLjJSyTmXvmstXeTHG4rbAm1HtL/view?usp=sharing)
 - [2주차 영상](https://drive.google.com/file/d/1R1Mjlr5Y0Pl_4wG_M6nOKJTBQZtZmAoq/view?usp=sharing)

---
 
 ### Asset Reference 
 
 - [Animated Top Down Survivor Player](https://opengameart.org/content/animated-top-down-survivor-player) by Riley Gombart, [CC BY](https://creativecommons.org/licenses/by/3.0/) 3.0
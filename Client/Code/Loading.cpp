#include "stdafx.h"
#include "..\Header\Loading.h"
#include "GraphicDev.h"
#include "ManageMent.h"
#include "../Header/SceneIntro.h"
#include "../Header/Camera.h"
#include "Texture.h"
#include "../Header/CameraDynamic.h"
#include "InputDev.h"
#include "Renderer.h"
#include "../Header/Player.h"
#include "../Header/UI_Header.h"
#include "../Header/Effect_Header.h"
#include "../Header/FireBullet.h"
#include "../Header/CrossBowArrow.h"
#include "../Header/SharpBullet.h"
#include "../Header/CrossBow.h"



#include "../Header/Item_Header.h"
#include "../Header/Static_Object.h"
#include "../Header/BuildObject_Header.h"
#include "../Header/StatUI_Header.h"
#include "../Header/Decal_Header.h"
_USING(Client)


HRESULT CLoading::Load_Static()
{
	if (FAILED(Load_Static_Shader()))
		return E_FAIL;

	if (FAILED(Load_Static_Texture()))
		return E_FAIL;

	if (FAILED(Load_Static_StaticMesh()))
		return E_FAIL;

	if (FAILED(Load_Static_DynamicMesh()))
		return E_FAIL;

	if (FAILED(Load_StaticObject()))
		return E_FAIL;

	m_iComplete = 100;
	return NOERROR;
}

HRESULT CLoading::Load_StaticObject()
{
	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CAMERA", CCameraDynamic::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PLAYER", CPlayer::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILLPANEL", CSkillPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALBACKGROUND", CVerticalBarBackGround::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALBACKGROUNDREV", CVerticalBarBackGroundRev::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALHP", CVerticalBarHP::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALMP", CVerticalBarMP::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALHPEFFECT", CVerticalBarHPEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"VERTICALMPEFFECT", CVerticalBarMPEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PANEL", CPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BLOODEFFECT", CBloodEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"FIREBULLET", CFireBullet::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CROSSBOWARROW", CCrossBowArrow::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SHARPBULLET", CSharpBullet::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SHARPBULLETEFFECT", CSharpBulletEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SHARPBULLETEXPLOSIVE", CSharpBulletExplosive::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"FIREBULLETEFFECT", CFireBulletEffect::Create(m_pGraphicDev))))
		return E_FAIL;
	m_iComplete = 90;
	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_1", CShotGun::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_2", CLightShot::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_3", CBuildIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_4", CBombIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_5", CPoisionFieldIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_6", CShieldIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_7", CMissileTowerIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CROSSBOW", CCrossBow::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"FIREBULLET_FIRE", CFireBulletFireEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MANA_TOKEN", CManaToken::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PRESENT_BOMB", CPresentBomb::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"FOG_EFFECT", CFogEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"POISION_FIELD", CPoisionField::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MONSTER_HP_BAR", CMonsterHpBar::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MONSTER_HP_FRAME", CMonsterHpFrame::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MONSTER_HP_CURR", CMonsterHpCurr::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"EXP_BAR", CExpBar::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"WAVE_PANEL", CWavePanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"WAVE_BAR", CWaveBar::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"WAVE_INFO", CWaveInfo::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"WAVE_BAR_CONTENT", CWaveBarContents::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BUILD_LOADING_BAR", CBuildLoadingBar::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BUILD_LOADING_CONTENT", CBuildLoadingContent::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PLAYER_INFO", CPlayerInfo::Create(m_pGraphicDev))))
		return E_FAIL;

	m_iComplete = 95;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MONSTER_HP_COLOR", CMonsterHpColor::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MONSTER_HP_FONT", CMonsterHpNum::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CRYSTAL", CCrystal::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CRYSTAL_CORE", CCrystalCore::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CRYSTAL_HEAD", CCrystalHead::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"CRYSTAL_RING", CCrystalRing::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SHIELD", CShield::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MISSILE_TOWER", CMissilTower::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"GLOWBALL", CGlowBall::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MISSILE_TOWER_BULLET", CMissileTowerBullet::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PROJECTILE", CProjectile::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"DAMAGE_BUFFER", CDamageBuffer::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"DAMAGE_FONT", CDamageFont::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PHASE", CPhase::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"WAVE_NUM", CWaveNum::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"STRIKE_TOWER", CStrikeTower::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LIGHTNING_TOWER", CLightningTower::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_9", CStrikeTowerIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_8", CLightningTowerIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_ICON_10", CHealIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"STAT_UI_PANEL", CStatPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"STAT_UI_BACKGROUND", CStatBackGround::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"DAMAGE_UP_ICON", CDamageUpIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"HEALTH_UP_ICON", CHealthUpIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"COOL_DOWN_ICON", CCoolDownIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MANA_DOWN_ICON", CManaDownIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PLAYER_INFO_PANEL", CPlayerInfoPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"EMPTY_PANEL", CEmptyPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"POINT_ICON", CPointIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"NUM_ICON", CNumIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"ATTACK_PANEL", CAttackPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_DAMAGE_PANEL", CSkillDamagePanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"HEALTH_PANEL", CHealthPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"COOL_PANEL", CCoolPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MANA_PANEL", CManaPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"DOT_ICON", CDotIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"PERCENT_ICON", CPercentIcon::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"POINT_NUM_PANEL", CPointNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"ATTACK_NUM_PANEL", CAttackNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SKILL_NUM_PANEL", CSkillDamageNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"HEALTH_NUM_PANEL", CHealthNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"COOL_NUM_PANEL", CCoolNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MANA_NUM_PANEL", CManaNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"ABILITY_NUM_PANEL", CAbilityNumPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LEVEL_PANEL", CLevelPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"NUMBER_UI", CNumberUI::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"NUMBER_PANEL", CNumberPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"TEXT_UI", CTextUI::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"TEXT_PANEL", CTextPanel::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LIGHTNING_BOLT", CLightningBolt::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"STRIKE_BEAM", CStrikeBeam::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BOMB_EFFECT", CBombEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LIGHTNING_EFFECT_SPHERE", CLightningSphere::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LIGHTNING_EFFECT_BOLT", CLightningBoltEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"ITEM_EFFECT", CItemEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BLUE_EXPLOSION", CBlueExplosion::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"YELLOW_EXPLOSION", CYellowExplosion::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"TOWER_HIT_EFFECT", CTowerHitEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"POISON_FIELD_EFFECT", CPoisonFieldEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"MOUSE_POINT", CMousePoint::Create(m_pGraphicDev))))
		return E_FAIL;	

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"SUMMONDECAL", CSummonDecal::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"RANGEDECAL", CRangeDecal::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BUILDPOINT", CBuildPoint::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"BUILD_EFFECT", CBuildEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LAVA_EFFECT", CLavaEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct_Prototype(SCENESTATIC, L"LAVA_FOG_EFFECT", CLavaFogEffect::Create(m_pGraphicDev))))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLoading::Load_Static_Texture()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BLOODEFFECT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Frame/Blood1/Blood_%d.png", 19), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SKYBOXTEX", CTexture::Create(m_pGraphicDev, L"../Texture/burger%d.dds", 1, CTexture::CUBE), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"PANEL", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Panel/Panel%d.tga", 11), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"VERTICALBAR", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/VerticalBar/VerticalBar%d.tga", 6), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHARPBULLET_EFFECT", CTexture::Create(m_pGraphicDev, L"Resource/StaticMesh/Bullet/Soul%d.png", 1), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHARPBULLETEXPLOSIVE", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Explode/Explode%d.tga", 4), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FIREBULLETEFFECT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Frame/Final_Fire02/Final_Fire%d.tga", 31), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SKILL_ICON", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/SkillIcon/SkillIcon%d.tga", 10), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FIREBULLET_FIRE", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/FireBulletEffect/FireBulletEffect%d.tga", 3), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FOG_EFFECT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Single/BS/fogSheet_%d.tga", 2), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MONSTER_UI", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/MonsterUI/MonsterUI%d.tga", 5), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MONSTER_FONT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Font/Skin/%d.png", 11), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DAMAGE_FONT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Font/Damage/%d.png", 11), SCENESTATIC)))
		return E_FAIL;

	m_iComplete = 15;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"PHASE", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Text/Phase/%d.png", 3), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WAVE_NUM", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Text/WaveNum/%d.png", 3), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FILTER", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Filter/%d.tga", 1), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"STAT_UI", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/StatUI/%d.tga",27), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"NUMBER_UI", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Font/Damage/White/%d.png", 12), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"TEXT_UI", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/TextPanel/%d.png", 6), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BOMB_EXPLOSION", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Frame/Explosion/explosionFlipbook_%d.tga",16), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LIGHTNING_EFFECT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/LightningEffect/LightningEffect%d.tga", 2), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"PARTICLE", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Particle/%d.png", 8), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DECAL", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/Decal/%d.tga", 4), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MOUSE_POINT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Mouse/%d.png", 3), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LAVA_EFFECT", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Effect/LavaEffect/%d.tga", 3), SCENESTATIC)))
		return E_FAIL;

	m_iComplete = 25;
	
	return NOERROR;
}

HRESULT CLoading::Load_Static_Shader()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADER", CShader::Create(m_pGraphicDev, L"ShaderFile/Shader.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADERUI", CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderUI.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADERVERTICAL", CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderVertical.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADERVERTICALEFFECT", CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderVerticalEffect.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADEREFFECT", CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderEffect.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADER_COOL", CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderUI_Cool.fx"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADER_TOWER_BULLET", CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Tower_Bullet.fx"), SCENESTATIC)))
		return E_FAIL;
	m_iComplete = 8;
	return NOERROR;
}

HRESULT CLoading::Load_Static_StaticMesh()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MAGUSQUARTER", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MagusQuarters/", L"MagusQuarters.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CROSSSTAIR", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/StairGroup_01/", L"StairGroup_01.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LONGSTAIR", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/StairGroup_02/", L"StairGroup_02.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHORTSTAIR", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/CoreStairs_withedges/", L"CoreStairs_withedges.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CROSSBOW", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/CrossBow/", L"CrossBow.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"ARCANEPAD", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/ArcanePad_HI/", L"ArcanePad_HI.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CROSSBOWARROW", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/CrossBowArrow/", L"CrossBowArrow.x"), SCENESTATIC)))
		return E_FAIL;

	m_iComplete = 37;
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FIREBULLET", CMeshStatic::Create(m_pGraphicDev, L"Resource/StaticMesh/FireBall/", L"FireBall.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHARPBULLET", CMeshStatic::Create(m_pGraphicDev, L"Resource/StaticMesh/Bullet/", L"Bullet.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"ARROW", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Arrow/", L"Arrow.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MANA_TOKEN", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/ManaToken/", L"ManaToken.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"PRESENT_BOMB", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Present/", L"Present.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CRYSTAL_CORE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Crystal/", L"Crystal.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CRYSTAL_HEAD", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Crystal/Accessory1/", L"Accessory1.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CRYSTAL_RING", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Crystal/Accessory2/", L"Accessory2.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"GLOWBALL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Effect/GlowBall/", L"GlowBall.x"), SCENESTATIC)))
		return E_FAIL;

	m_iComplete = 59;
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"HEAD_PROJECTILE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Effect/Head_Projectile/", L"Head_Projectile.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"PROJECTILE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Effect/Projectile1/", L"Projectile1.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CENTER_ARCH", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_14/", L"Group_14.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CENTER_WALL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_15/", L"Group_15.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BRIDGE_WALL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_11/", L"Group_11.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SET_RAIL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_45/", L"Group_45.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LONG_RAIL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WoodRailing_SingleWide_HI/", L"WoodRailing_SingleWide_HI.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DOUBLE_RAIL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_09/", L"Group_09.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"CRYSTAL_STAFF", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_41/", L"Group_41.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_DOUBLE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_34/", L"Group_34.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_TRIPLE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_03/", L"Group_03.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_ANGLE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_06/", L"Group_06.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_HEIGHT", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_35/", L"Group_35.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_SINGLE", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WallTorch_HI/", L"WallTorch_HI.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALLTORCH_LONG", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_36/", L"Group_36.x"), SCENESTATIC)))
		return E_FAIL;

	

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LIGHTNING_BOLT", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/Effect/Projectile2/", L"Projectile2.x"), SCENESTATIC)))
		return E_FAIL;
	m_iComplete = 67;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DOOR", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_25/", L"Group_25.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHORT_RAIL"		, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WoodRailingGroup_01/", L"WoodRailingGroup_01.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"ROOF"			, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/magusQuartersRoof_SM/", L"magusQuartersRoof_SM.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SINGLE_BRIDGE"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WallTrim_01_low/", L"WallTrim_01_low.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_0"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_16/", L"Group_16.x"), SCENESTATIC)))
		return E_FAIL;																							  
																												  
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_1"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_17/", L"Group_17.x"), SCENESTATIC)))
		return E_FAIL;																							 
																												 
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_2"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_19/", L"Group_19.x"), SCENESTATIC)))
		return E_FAIL;																							  
																												  
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_3"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_43/", L"Group_43.x"), SCENESTATIC)))
		return E_FAIL;																							  
																												  
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_4"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Wall_Banner01A/", L"Wall_Banner01A.x"), SCENESTATIC)))
		return E_FAIL;																							 
																												 
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_5"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WallBanner_Large_HI/", L"WallBanner_Large_HI.x"), SCENESTATIC)))
		return E_FAIL;																							  
																												  
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"WALL_BANNER_6"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/WallBanner_Small_HI/", L"WallBanner_Small_HI.x"), SCENESTATIC)))
		return E_FAIL;
	
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SIDE_STAIR"	, CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/CoreStairs_3x_cnr/", L"CoreStairs_3x_cnr.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LARGE_CRYSTAL", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/LargeCrystalLight_HI/", L"LargeCrystalLight_HI.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BARREL_0", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Barrel_HI/", L"Barrel_HI.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BARREL_1", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_29/", L"Group_29.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BARREL_2", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_31/", L"Group_31.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BARREL_3", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_32/", L"Group_32.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"TABLE_0", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_27/", L"Group_27.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"TABLE_1", CMeshStatic::Create(m_pGraphicDev, L"Resource/Mesh/StaticMesh/MapObject/Group_37/", L"Group_37.x"), SCENESTATIC)))
		return E_FAIL;

	m_iComplete = 73;
	return NOERROR;
}

HRESULT CLoading::Load_Static_DynamicMesh()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"HUNTRESS", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/Huntress/", L"Huntress.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DEMON", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/Demon/", L"Demon.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"TRESURECHEST", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/TresureChest/", L"TresureChest.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"DARKELFARCHER", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/DarkElfArcher/", L"DarkElfArcher.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"GOBLIN", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/Goblin/", L"Goblin.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"KOBOLD", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/Kobold/", L"Kobold.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHIELD", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/MageBlockade/", L"MageBlockade.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LIGHTNIG_TOWER", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/LightningTower/", L"LightningTower.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"MISSILE_TOWER", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/MissleTower/", L"MissleTower.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"ORCBRUISER", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/OrcBruiser/", L"OrcBruiser.x"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"STRIKE_TOWER", CMeshDynamic::Create(m_pGraphicDev, L"Resource/Mesh/DynamicMesh/StrikerTower/", L"StrikerTower.x"), SCENESTATIC)))
		return E_FAIL;
	
	m_iComplete = 87;
	return NOERROR;
}

CLoading::CLoading(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:m_pGraphicDev(_m_pGraphicDev),
	m_pComponentMgr(CComponentMgr::GetInstance())
{
	m_pGraphicDev->AddRef();
	m_pComponentMgr->AddRef();
}

HRESULT CLoading::Initialize(SCENEID eSceneID)
{
	m_eSceneID = eSceneID;

	InitializeCriticalSection(&m_CS);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 1, Thread_Main, this, 0, nullptr);
	if (m_hThread == nullptr)
		return E_FAIL;

	return NOERROR;
}

_uint CLoading::Thread_Main(void * Arg)
{
	CLoading*	pLoading = (CLoading*)Arg;

	EnterCriticalSection(&pLoading->m_CS);

	HRESULT hResult;
	
	hResult=pLoading->Load_Static();	

	if (FAILED(hResult))
		return -1;

	LeaveCriticalSection(&pLoading->m_CS);

	return _uint(0);
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, SCENEID eSceneID)
{
	CLoading*	pInstance = new CLoading(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize(eSceneID)))
	{
		_MSGBOX("CLoading Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_CS);
	
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pComponentMgr);
}

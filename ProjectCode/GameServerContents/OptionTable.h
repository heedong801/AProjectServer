#pragma once
#include <GameServerNet\DBQuery.h>


class OptionRow : public std::enable_shared_from_this<OptionRow>
{
public:
	int			ItemIndex;
	int			Att;
	int			Armor;
	int			HpMax;
	int			MpMax;
	int			Hp;
	int			Mp;
	int			HpRecovery;
	int			MpRecovery;
	int			CriticalPercent;
	int			CriticalDamage;

public:
	OptionRow()
	{
	}

	OptionRow(
		int			_ItemIndex,
	int			_Att,
	int			_Armor,
	int			_HpMax,
	int			_MpMax,
	int			_Hp,
	int			_Mp,
	int			_HpRecovery,
	int			_MpRecovery,
	int			_CriticalPercent,
	int			_CriticalDamage
	)
		: ItemIndex(_ItemIndex),
	Att(_Att),
	Armor(_Armor),
	HpMax(_HpMax),
	MpMax(_MpMax),
	Hp(_Hp),
	Mp(_Mp),
	HpRecovery(_HpRecovery),
	MpRecovery(_MpRecovery),
	CriticalPercent(_CriticalPercent),
	CriticalDamage(_CriticalDamage)

	{
	}
};

class OptionTable_SelectItemOption : public DBQuery
{
public:
	int ItemIdx;
	std::shared_ptr<OptionRow> RowData;

public:
	OptionTable_SelectItemOption(int _ItemIdx);
	bool DoQuery() override;
};


/*************************************************************************

　プロジェクトを作り直すのが面倒だったので、こんな感じに型名を切り替えるよ
うにしました。
　新しいプロジェクトが必要な場合は、新しいクラスを作ってください。テンプレ
を用意しときます。テンプレとそれまでの奴があってないように見えますが、気に
しないでください。早急に修正しときます。

*************************************************************************/

#include <avr/io.h>

#include <MainCircit/MainCircit.h>

namespace On2017
{

//Zephyranthes
#include "OnSeason_Project_class/01_Zephyranthes/Project5.h" //Warhead
#include "OnSeason_Project_class/01_Zephyranthes/Project6.h" //Catapult
#include "OnSeason_Project_class/01_Zephyranthes/Project7.h" //Shotgun

//Physalis
#include "OnSeason_Project_class/02_Physalis/Project8.h"  //Kerberos-chan
#include "OnSeason_Project_class/02_Physalis/Project9.h"  //OneWayTicket
#include "OnSeason_Project_class/02_Physalis/Project10.h" //Otegine

//Dendrobium
#include "OnSeason_Project_class/03_Dendrobium/Project_11.h" //

//Gerbera
#include "OnSeason_Project_class/05_Gerbera/Project_12.h" //
#include "OnSeason_Project_class/05_Gerbera/Project_13.h" //
#include "OnSeason_Project_class/05_Gerbera/Project_14.h" //

}

#include "OffSeason_Project_class/01_Akiduki/TecnicSteer.h"
#include "OffSeason_Project_class/02_Teruduki/AIG_No_0.h"
#include "OffSeason_Project_class/02_Teruduki/Gourobo_Cteam.h"

int main()
{	
//	On2017::Gerbera::BanriFinal::Main _machine;
	Off2017::Akiduki::TecnicSteer::Main _machine;
//	Off2017::Teruduki::AIG_No_0::Main _machine;
//	Off2017::Teruduki::Gourobo_Cteam::Main _machine;
	
	while (1)
	{
		_machine.Input();
		
		_machine.Process();
		
		_machine.Output();
	}
}

/************************************************************************/


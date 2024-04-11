#if 0
#include "BaseVSShader.h"

CREATE_CONSTANT_BUFFER( Test )
{
	float x;
};

BEGIN_VS_SHADER( TestDX11, "Help for TestDX11" )

	BEGIN_SHADER_PARAMS
	END_SHADER_PARAMS

	DECLARE_CONSTANT_BUFFER( Test )

	SHADER_INIT
	{
		INIT_CONSTANT_BUFFER( Test );
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			//SET_CONSTANT_BUFFER( Test );
		}

		DYNAMIC_STATE
		{
			CONSTANT_BUFFER_TYPE(Test) temp;
			temp.x = 5.0f;
			UPDATE_CONSTANT_BUFFER(Test, temp);
		}

		Draw();
	}

END_SHADER
#endif
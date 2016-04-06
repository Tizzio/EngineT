Header
{
	Name: Unlit
	Version: 330
	Mesh: On
	GammaCorrection: Off
}

Vertex
{
	out vec2 vTexCoord;
	
	void PreVertex() {}
	
	void PostVertex()
	{
		vTexCoord = inTexCoord;
	}
}

Geometry
{

}

Fragment
{
	in vec2 vTexCoord;
	uniform sampler2D uSampler;

	void PreFragment() {}
	void PostFragment()
	{
		fragColor.rgb *= texture2D(uSampler, vTexCoord.xy).rgb;
	}
}
 
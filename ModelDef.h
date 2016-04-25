#pragma once
#include "XMLloader.h"
#include <SFML\Graphics.hpp>
#include "utility.h"
#include "Vector2D.h"

using namespace sf;




class ModelDef
{
public:
	ModelDef(Vector2f const& _pos = Vector2f(), float _rot = 0, Vector2f const& _scale = Vector2f(), float _rotAround = 0,
		float _clR = 0, float _clG = 0, float _clB = 0, float _clA = 0)
		: pos(_pos), rot(_rot), scale(_scale), rotAround(_rotAround),
		clR(_clR), clG(_clG), clB(_clB), clA(_clA)
	{

	}
	void set(ModelDef& s)
	{
		(*this) = s;
	}
	void setRandom(const ModelDef& dMin, const ModelDef& dMax)
	{
		pos.x = randRange(dMin.pos.x, dMax.pos.x);
		pos.y = randRange(dMin.pos.y, dMax.pos.y);

		posNoRot.x = randRange(dMin.posNoRot.x, dMax.posNoRot.x);
		posNoRot.y = randRange(dMin.posNoRot.y, dMax.posNoRot.y);

		scale.x = randRange(dMin.scale.x, dMax.scale.x);
		scale.y = randRange(dMin.scale.y, dMax.scale.y);

		rot = randRange(dMin.rot, dMax.rot);
		rotAround = randRange(dMin.rotAround, dMax.rotAround);


		clR = randRange(dMin.clR, dMax.clR);
		clG = randRange(dMin.clG, dMax.clG);
		clB = randRange(dMin.clB, dMax.clB);
		clA = randRange(dMin.clA, dMax.clA);
	}

	void deserialize(XMLloader& loader, const ModelDef& _default = ModelDef())
	{
		

		ModelDef defMax, defMin;
		defMin.deserialize(loader, _default, "");
		defMax.deserialize(loader, defMin, "_max");

		setRandom(defMin, defMax);
		
		
		/*pos.x = randRange(pos.x, loader.load("posX_max", pos.x));
		pos.y = randRange(pos.y, loader.load("posY_max", pos.y));

		posNoRot.x = randRange(posNoRot.x, loader.load("posNoRotX_max", posNoRot.x));
		posNoRot.y = randRange(posNoRot.y, loader.load("posNoRotY_max", posNoRot.y));

		scale.x = randRange(scale.x, loader.load("scaleX_max", scale.x));
		scale.y = randRange(scale.y, loader.load("scaleY_max", scale.y));

		rot = randRange(rot, loader.load("rot_max", rot));
		rotAround = randRange(rotAround, loader.load("rotAround_max", rotAround) );

		clR = randRange(clR, loader.load("clR_max", clR));
		clG = randRange(clG, loader.load("clG_max", clG));
		clB = randRange(clB, loader.load("clB_max", clB));
		clA = randRange(clA, loader.load("clA_max", clA));*/
	}
	void deserialize(XMLloader& loader, const ModelDef& _default, const string& addictionalPartOfName)
	{
		pos.x = loader.load("posX" + addictionalPartOfName, _default.pos.x);
		pos.y = loader.load("posY" + addictionalPartOfName, _default.pos.y);

		posNoRot.x = loader.load("posNoRotX" + addictionalPartOfName, _default.posNoRot.x);
		posNoRot.y = loader.load("posNoRotY" + addictionalPartOfName, _default.posNoRot.y);

		scale.x = loader.load("scaleX" + addictionalPartOfName, _default.scale.x);
		scale.y = loader.load("scaleY" + addictionalPartOfName, _default.scale.y);

		rot = loader.load("rot" + addictionalPartOfName, _default.rot);
		rotAround = loader.load("rotAround" + addictionalPartOfName, _default.rotAround);

		clR = loader.load("clR" + addictionalPartOfName, _default.clR);
		clG = loader.load("clG" + addictionalPartOfName, _default.clG);
		clB = loader.load("clB" + addictionalPartOfName, _default.clB);
		clA = loader.load("clA" + addictionalPartOfName, _default.clA);
	}

	// if an statistic is not in the range of min max
	// became equal to the closest gate
	void clamp(const ModelDef& min, const ModelDef& max)
	{
		pos.x = ::clamp(pos.x, min.pos.x, max.pos.x);
		pos.y = ::clamp(pos.y, min.pos.y, max.pos.y);
		posNoRot.x = ::clamp(posNoRot.x, min.posNoRot.x, max.posNoRot.x);
		posNoRot.y = ::clamp(posNoRot.y, min.posNoRot.y, max.posNoRot.y);
		scale.x = ::clamp(scale.x, min.scale.x, max.scale.x);
		scale.y = ::clamp(scale.y, min.scale.y, max.scale.y);

		rot = ::clamp(rot, min.rot, max.rot);
		rotAround = ::clamp(rotAround, min.rotAround, max.rotAround);

		clR = ::clamp(clR, min.clR, max.clR);
		clG = ::clamp(clG, min.clG, max.clG);
		clB = ::clamp(clB, min.clB, max.clB);
		clA = ::clamp(clA, min.clA, max.clA);
	}
	bool equalOneOf(const ModelDef& min, const ModelDef& max)
	{
		bool b = true;
		b = b && (pos == min.pos || pos == max.pos);
		b = b && (posNoRot == min.posNoRot || posNoRot == max.posNoRot);
		b = b && (scale == min.scale || scale == max.scale);

		b = b && (rot == min.rot || rot == max.rot);
		b = b && (rotAround == min.rotAround || rotAround == max.rotAround);

		b = b && (clR == min.clR || clR == max.clR);
		b = b && (clG == min.clG || clG == max.clG);
		b = b && (clB == min.clB || clB == max.clB);
		b = b && (clA == min.clA || clA == max.clA);

		return b;
	}

	// oprerators

	void operator+=(const ModelDef& model)
	{
		pos += model.pos;
		pos += model.posNoRot;
		scale += model.scale;
		rot += model.rot;
		rotAround += model.rotAround;
		clR += model.clR;
		clG += model.clG;
		clB += model.clB;
		clA += model.clA;
	}
	void operator-=(const ModelDef& model)
	{
		pos -= model.pos;
		pos -= model.posNoRot;
		scale -= model.scale;
		rot -= model.rot;
		rotAround -= model.rotAround;
		clR -= model.clR;
		clG -= model.clG;
		clB -= model.clB;
		clA -= model.clA;
	}

	void operator*=(const ModelDef& model)
	{
		pos.x *= model.pos.x;
		pos.y *= model.pos.y;
		posNoRot.x *= model.posNoRot.x;
		posNoRot.y *= model.posNoRot.y;

		scale.x *= model.scale.x;
		scale.y *= model.scale.y;

		rot *= model.rot;
		rotAround *= model.rotAround;
		clR *= model.clR;
		clG *= model.clG;
		clB *= model.clB;
		clA *= model.clA;
	}
	void operator/=(const ModelDef& model)
	{
		pos.x /= model.pos.x;
		pos.y /= model.pos.y;
		posNoRot.x /= model.posNoRot.x;
		posNoRot.y /= model.posNoRot.y;

		scale.x /= model.scale.x;
		scale.y /= model.scale.y;

		rot /= model.rot;
		rotAround /= model.rotAround;
		clR /= model.clR;
		clG /= model.clG;
		clB /= model.clB;
		clA /= model.clA;
	}


	ModelDef operator+(const ModelDef& model)
	{
		ModelDef def;
		def.pos += model.pos;
		def.posNoRot += model.posNoRot;
		def.scale += model.scale;
		def.rot += model.rot;
		def.rotAround += model.rotAround;
		def.clR += model.clR;
		def.clG += model.clG;
		def.clB += model.clB;
		def.clA += model.clA;
		return def;
	}
	ModelDef operator-(const ModelDef& model)
	{
		ModelDef def;
		def.pos -= model.pos;
		def.posNoRot -= model.posNoRot;
		def.scale -= model.scale;
		def.rot -= model.rot;
		def.rotAround -= model.rotAround;
		def.clR -= model.clR;
		def.clG -= model.clG;
		def.clB -= model.clB;
		def.clA -= model.clA;
		return def;
	}

	ModelDef operator*(float s) const
	{
		ModelDef r;
		r.pos = pos*s;
		r.posNoRot = posNoRot*s;
		r.scale = scale *s;

		r.rot = rot * s;
		r.rotAround = rotAround *s;

		r.clA = clA *s;
		r.clB = clB *s;
		r.clG = clG *s;
		r.clA = clA *s;
		return r;
	}
	ModelDef operator/(float s) const
	{
		ModelDef r;
		r.pos = pos / s;
		r.posNoRot = posNoRot / s;
		r.scale = scale / s;

		r.rot = rot / s;
		r.rotAround = rotAround / s;

		r.clA = clA / s;
		r.clB = clB / s;
		r.clG = clG / s;
		r.clA = clA / s;
		return r;
	}

	bool operator== (ModelDef const& other)
	{
		return pos == other.pos
			&& posNoRot == other.posNoRot
			&& scale == other.scale
			&& rot == other.rot
			&& rotAround == other.rotAround
			&& clR == other.clR
			&& clG == other.clG
			&& clB == other.clB
			&& clA == other.clA;
	}
	bool operator!= (ModelDef const& other)
	{
		return pos != other.pos
			&& posNoRot != other.posNoRot
			&& scale != other.scale
			&& rot != other.rot
			&& rotAround != other.rotAround
			&& clR != other.clR
			&& clG != other.clG
			&& clB != other.clB
			&& clA != other.clA;
	}

	ModelDef countAfterOffset( ModelDef initial)
	{
		/*float alfa = ((parent.getRotation() + rotAround)* M_PI) / 180.f;
		sf::Vector2f v, p(pos.x * parent.getScale().x, pos.y * parent.getScale().y);

		v.x = p.x * cos(alfa) - p.y * sin(alfa);
		v.y = p.x * sin(alfa) + p.y * cos(alfa);

		setRotation(parent.getRotation() + rot);
		setPosition(parent.getPosition() + v);

		sf::Sprite::setScale(ModelDef::scale.x * parent.getScale().x,
			ModelDef::scale.y * parent.getScale().y);*/

		initial.pos += pos.getRotated(initial.rot + rotAround);
		///////
		initial.scale *= scale;
		initial.rot += rot;

		// color nondepended from intial
		initial.clA = clA;
		initial.clR = clR;
		initial.clG = clG;
		initial.clB = clB;
	}


	// data
	// can be used as offset or real information
	Vector2D pos, scale, posNoRot;
	float rot, rotAround;
	float clR, clG, clB, clA;

};
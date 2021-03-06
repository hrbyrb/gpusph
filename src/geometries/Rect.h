/*  Copyright (c) 2011-2018 INGV, EDF, UniCT, JHU

    Istituto Nazionale di Geofisica e Vulcanologia, Sezione di Catania, Italy
    Électricité de France, Paris, France
    Università di Catania, Catania, Italy
    Johns Hopkins University, Baltimore (MD), USA

    This file is part of GPUSPH. Project founders:
        Alexis Hérault, Giuseppe Bilotta, Robert A. Dalrymple,
        Eugenio Rustico, Ciro Del Negro
    For a full list of authors and project partners, consult the logs
    and the project website <https://www.gpusph.org>

    GPUSPH is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GPUSPH is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GPUSPH.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * File:   Rect.h
 * Author: alexis
 *
 * Created on 14 juin 2008, 17:04
 */

#ifndef _RECT_H
#define	_RECT_H

#include "Object.h"
#include "Point.h"
#include "Vector.h"


class Rect: public Object {
	private:
		Point   m_origin;
		double	m_lx, m_ly;
		Vector	m_vx, m_vy;
		Vector	m_vz; // normal vector

	public:
		Rect(void);
		Rect(const Point&, const double, const double, const EulerParameters & = EulerParameters());
		Rect(const Point&, const Vector&, const Vector&);
		virtual ~Rect(void) {};

		double Volume(const double) const;
		void SetInertia(const double);

		void FillBorder(PointVect&, const double);
		void FillBorder(PointVect&, const double, const bool,
				const bool, const int);

		void Fill(PointVect&, const double, const bool*);
		void Fill(PointVect&, PointVect&, PointVect&, std::vector<uint4>&, const double, const int, std::vector<uint> [][4]);
		int Fill(PointVect&, const double, const bool, const bool);
		int Fill(PointVect&, const double, const bool fill = true);
		void FillIn(PointVect& points, const double dx, const int layers);
		bool IsInside(const Point&, const double) const;

		void setEulerParameters(const EulerParameters &ep);
		void getBoundingBox(Point &output_min, Point &output_max);
		void shift(const double3 &offset);

#if USE_CHRONO == 1
		void BodyCreate(::chrono::ChSystem *bodies_physical_system, const double dx, const bool collide,
			const ::chrono::ChQuaternion<> & orientation_diff)
		{ throw std::runtime_error("Rect::BodyCreate not implemented !"); };
#else
		void BodyCreate(void *p1, const double p2, const bool p3)
		{ Object::BodyCreate(p1, p2, p3); }
#endif
};
#endif	/* _RECT_H */

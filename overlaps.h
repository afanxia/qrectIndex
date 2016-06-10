//Nitro C++ proficiency assessment coded by Martin Gladnishki
#ifndef				_OVERLAPS_
#define				_OVERLAPS_

#include			<map>
#include			<vector>

#define				BYTE_BITS			8
#define				UCHAR_BITS			(BYTE_BITS * sizeof(UCHAR))
#define				USHORT_BITS			(BYTE_BITS * sizeof(USHORT))
#define				UINT_BITS			(BYTE_BITS * sizeof(UINT))

#define				MIN(a, b)			(a < b ? a : b)
#define				MAX(a, b)			(a > b ? a : b)

typedef				unsigned int		BOOL;
typedef				unsigned char		UCHAR;
typedef				unsigned short		USHORT;
typedef				unsigned int		UINT;
typedef				unsigned long long	ULONG;

//---------------------------------------------------------------
#define				OP_DECL( op, t )	operator op( const t& r )
#define				OP_BODY( op, t )	return t( u.i op r.u.i, v.i op r.v.i )
#define				OP_BODY_B( op, c )	return (u op r.u) c (v op r.v)
#define				OP_BODY_B_S( op )   return (i op r.i)

union				scalar2
{					UINT	i; 
					scalar2(): i(0) {}
					scalar2( UINT _i ): i(_i) {}
					scalar2( const scalar2& _s ): i(_s.i) {}
	BOOL			OP_DECL( ==,scalar2)const		{ OP_BODY_B_S( == ); }
	BOOL			OP_DECL( !=,scalar2)const		{ OP_BODY_B_S( != ); }
	BOOL			OP_DECL(  <,scalar2)const		{ OP_BODY_B_S(  < ); }
	BOOL			OP_DECL(  >,scalar2)const		{ OP_BODY_B_S(  > ); }
	BOOL			OP_DECL( <=,scalar2)const		{ OP_BODY_B_S( <= ); }
	BOOL			OP_DECL( >=,scalar2)const		{ OP_BODY_B_S( >= ); }
	BOOL			OP_DECL(  +,scalar2)const		{ OP_BODY_B_S(  + ); }
	BOOL			OP_DECL(  -,scalar2)const		{ OP_BODY_B_S(  - ); }
	BOOL			OP_DECL(  *,scalar2)const		{ OP_BODY_B_S(  * ); }
	BOOL			OP_DECL(  /,scalar2)const		{ OP_BODY_B_S(  / ); }
	BOOL			OP_DECL(  &,scalar2)const		{ OP_BODY_B_S(  & ); }
	BOOL			OP_DECL(  |,scalar2)const		{ OP_BODY_B_S(  | ); }
	BOOL			OP_DECL(  ^,scalar2)const		{ OP_BODY_B_S(  ^ ); }
	BOOL			OP_DECL( <<,scalar2)const		{ OP_BODY_B_S( << ); }
	BOOL			OP_DECL( >>,scalar2)const		{ OP_BODY_B_S( >> ); }
	scalar2			min( scalar2 r )	const		{ return scalar2( MIN( i, r.i ) ); }
	scalar2			max( scalar2 r )	const		{ return scalar2( MAX( i, r.i ) ); }
};

struct				vec2
{					scalar2			u, v;
					vec2(): u(), v() {}
					vec2( const vec2& _s ): u(_s.u), v(_s.v) {}
					vec2( UINT _i ): u(_i), v(_i) {}
					vec2( UINT _u, UINT _v ): u(_u), v(_v) {}
	BOOL			OP_DECL( ==, vec2 )	const		{ OP_BODY_B( ==, && ); }
	BOOL			OP_DECL( !=, vec2 )	const		{ OP_BODY_B( !=, || ); }
	vec2			OP_DECL(  <, vec2 )	const		{ OP_BODY(  <, vec2); }
	vec2			OP_DECL(  >, vec2 )	const		{ OP_BODY(  >, vec2); }
	vec2			OP_DECL( <=, vec2 )	const		{ OP_BODY( <=, vec2 ); }
	vec2			OP_DECL( >=, vec2 )	const		{ OP_BODY( >=, vec2 ); }
	vec2			OP_DECL(  +, vec2 )	const		{ OP_BODY(  +, vec2); }
	vec2			OP_DECL(  -, vec2 )	const		{ OP_BODY(  -, vec2); }
	vec2			OP_DECL(  *, vec2 )	const		{ OP_BODY(  *, vec2); }
	vec2			OP_DECL(  /, vec2 )	const		{ OP_BODY(  /, vec2); }
	vec2			OP_DECL(  &, vec2 )	const		{ OP_BODY(  &, vec2); }
	vec2			OP_DECL(  |, vec2 )	const		{ OP_BODY(  |, vec2); }
	vec2			OP_DECL(  ^, vec2 )	const		{ OP_BODY(  ^, vec2); }
	vec2			OP_DECL( <<, vec2 )	const		{ OP_BODY( <<, vec2 ); }
	vec2			OP_DECL( >>, vec2 )	const		{ OP_BODY( >>, vec2 ); }
	vec2			min( const vec2 r )	const		{ return vec2( u.min( r.u ).i, v.min( r.v ).i ); }
	vec2			max( const vec2 r )	const		{ return vec2( u.max( r.u ).i, v.max( r.v ).i ); }
	UINT			index()				const		{ return u.i + 2 * v.i; }
	ULONG			key()				const		{ return u.i | (((ULONG)v.i) << UINT_BITS); }
};

//---------------------------------------------------------------
struct				rect: public std::vector<UINT>
{					vec2 u, v;
					rect(): u(), v() {}
					rect( const rect& _s ): u(_s.u), v(_s.v) { insert( end(), _s.begin(), _s.end() ); }
					rect( vec2 _u, UINT w, UINT h, UINT id ): u(_u), v(_u + vec2(w, h) - 1) { push_back( id ); }
					rect( vec2 _u, vec2 _v ): u(_u), v(_v) {}
					rect( vec2 _u, vec2 _v, rect& l, rect& r ): u(_u), v(_v)
					{
						insert( end(), l.begin(), l.end() );
						insert( end(), r.begin(), r.end() );
					}
	BOOL			equals( rect r )		const	{ return (u == r.u) && (v == r.v); }
	BOOL			valid()					const	{ return ((u <= v).index() == 3); }
	rect			intersection( rect r )	const	{ return rect( u.max( r.u ), v.min( r.v ), r, (rect&)*this ); }
	UINT			width()					const	{ return (v - u + 1).u.i; }
	UINT			height()				const	{ return (v - u + 1).v.i; }
	ULONG			keyU()					const	{ return u.key(); }
	ULONG			keyV()					const	{ return v.key(); }
};

//---------------------------------------------------------------
#define				Q_LEVELS		UINT_BITS
#define				Q_POWER(l)		(Q_LEVELS - (UINT)(l))
#define				Q_MASK(l)		((1 << (UINT)(l)) - 1)
#define				Q_EXTENT(l)		((UINT)-1 >> (l))

#define				QF_T_MASK		0x0F
#define				 QF_T_U			0x01
#define				 QF_T_R			0x02
#define				 QF_T_D			0x04
#define				 QF_T_L			0x08

typedef				std::vector<rect> rect_list;

static				UCHAR	const	NBR_F[4][2]	= { {QF_T_L,QF_T_U}, {QF_T_U,QF_T_R}, {QF_T_D,QF_T_L}, {QF_T_R,QF_T_D} };
static				UINT	const	NBR_S[4][2]	= { {	  3,	 0}, {	   0,	  1}, {		2,	   3}, {	 1,		2} };
static				vec2	const	OFS_D[4]	= { vec2( 0,	-1), vec2(+1,	  0), vec2( 0,	  +1), vec2(-1,		0) };
static				vec2	const	OFS_Z[4]	= { vec2( 0,	 0), vec2( 1,	  0), vec2( 0,	   1), vec2( 1,		1) };

struct				quad: public rect_list
{					vec2	o;
					UCHAR	s, pad;
					quad(): o(0), s(0), pad(0) {}
					quad( UCHAR _s, vec2 _o ): o(_o), s(_s), pad(0) {}
					quad( const quad& _s ): o(_s.o), s(_s.s) { insert( end(), _s.begin(), _s.end() ); }
	BOOL			equals( quad q )		const	{ return (o == q.o) && (s == q.s); }	
	BOOL			valid()					const	{ return (Q_LEVELS > s); }
	BOOL			contains( rect r )		const	{ return intersection( r ).equals( r ); }
	rect			intersection( rect r )	const	{ return rect( origin(), limit() ).intersection( r ); }
	vec2			origin()				const	{ return o << Q_POWER( s ); }
	vec2			limit()					const	{ return origin() + extent() ;}
	vec2			center()				const	{ return o + extent() / 2; }
	UINT			extent()				const	{ return Q_EXTENT( s ); }
	UINT			index()					const	{ return (o & 1).index(); }
	ULONG			key()					const	{ return center().key(); }
	quad			child()					const	{ return quad( s + 1, o << 1 ); }
	quad			parent()				const	{ return quad( s - 1, o >> 1 );	 }
	quad			neighbor( UINT ni = 0 ) const	{ return quad( s, (o + OFS_D[ni & 3]) & Q_MASK( s ) ); }
	quad			sibling( UINT si = 0 )	const	{ return quad( s, (o & ~1) | OFS_Z[si & 3] ); }
};

//---------------------------------------------------------------
struct rect_comp: public std::binary_function<rect, rect, BOOL>
{
    BOOL			operator()(const rect& l, const rect& r) const
	{
		if( l.keyU() < r.keyU() ) return true;
		if( l.keyU() > r.keyU() ) return false;
		if( l.keyV() < r.keyV() ) return true;
		return false;
	}
};

struct quad_comp: public std::binary_function<quad, quad, BOOL>
{
    BOOL			operator()(const quad& l, const quad& r) const
	{
		return (l.key() < r.key());
	}
};

typedef				std::map<rect, rect, rect_comp>	overlaps;
typedef				std::map<quad, quad, quad_comp> quadtree;

class				qtree: public quadtree
{
public:
	void			add( rect r )					{ add( r, root ); }
	void			get_overlaps( rect_list& list )
	{
		for( overlaps::iterator it = overlap_list.begin(); it != overlap_list.end(); it++ )
			list.push_back( it->second );
		std::sort( list.begin(), list.end(), rect_sort );
	}
private:
	overlaps		overlap_list;
	quad			root;

	void			add( rect& r, quad& q, BOOL overlap = true )
	{
		//validate arguments
		if( !r.valid() || !q.valid() )
			return;

		//find the tightest bounding quad
		BOOL entry = true;
		for( int i = 0; i < 4; i++ )
		{
			//collect intersections from existing quads
			if( overlap && entry && (find( q ) != end()) )
			{
				rect_list t;
				q = (*this)[q];
				for( quad::iterator it = q.begin(); it != q.end(); it++ )
				{
					rect x = r.intersection( *it );
					if( !x.valid() )
						continue;
					overlap_list[x] = x ;
					t.push_back( x );
				}
				for( rect_list::iterator it = t.begin(); it != t.end(); it++ )
					add( *it, q, false );
			}

			//iterate current quad's children
			quad s = q.child().sibling( i );
			if( !s.contains( r ) )
			{
				entry = false;
				continue;
			}
			q = s;
			i = -1;
			entry = true;
		}

		//create quad and register rectangle into it
		q.push_back( r );
		(*this)[q] = q;
	}

	static BOOL rect_sort( const rect& l, const rect& r )
	{
		if( l.size() < r.size() )
			return true;
		if( l.size() > r.size() )
			return false;
		for( std::vector<UINT>::const_iterator itl = l.begin(), itr = r.begin(); itl != l.end(); itl++, itr++ )
		{
			if( *itl < *itr )
				return true;
			if( *itl > *itr )
				return false;
		}
		return false;
	}
};

#endif //_OVERLAPS_
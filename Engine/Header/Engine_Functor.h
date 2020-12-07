#pragma once


namespace Engine
{
	class CFind_Tag
	{
	private:
		const _tchar* m_pszTag = nullptr;
	public:
		explicit CFind_Tag(const _tchar* _m_pszTag) :m_pszTag(_m_pszTag) {}
		~CFind_Tag() = default;

		template<typename T>
		bool operator() (T Pair)
		{
			return !lstrcmp(Pair.first, m_pszTag);
		}
	};


}
namespace NovelRT::Graphics
{
    class GraphicsCharacterRenderDataHelper
    {
      public:
        static inline int32_t getAdvanceDistance(FT_Pos rawAdvanceDistance)
        {
            return static_cast<int32_t>(rawAdvanceDistance);
        }
    };
} // namespace NovelRT::Graphics

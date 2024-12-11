
namespace mlib {

  namespace body {
    class object {
    private:
      float feeling_pain;
      float feeling_reduce_per_tick;

    public:
      void tick() {

        feeling_pain -= feeling_reduce_per_tick;
        if (feeling_pain < 0) feeling_pain = 0;
      }
      void damage(float _v) {
        feeling_pain += _v;
      }
      float get_feeling_pain() {
        return feeling_pain;
      }
    };
  }
}
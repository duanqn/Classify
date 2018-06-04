#ifndef SATARGET_H_
#define SATARGET_H_
class SAtarget {
  protected:
  // Hyperparameters
  double m_initTemp;
  double m_alpha; // 0 < alpha < 1 drop temperature
  double m_stopTemp;
  int m_MarkovLen;

  // Latent variables
  double func;
  double temp;
  int steps;

  public:
  // Supply hyperparameters
  SAtarget(double initTemp, double alpha, double stopTemp, int Markov);

  virtual ~SAtarget();

  virtual void run();

  virtual double evalEntropy() = 0;

  virtual void applyRandomMove() = 0;

  virtual void undoLastMove() = 0;
};
#endif // SATARGET_H_
#ifndef __QR_H__
#define __QR_H__

/**
  \file
  \f$QR\f$-����������.

  ���� �������� �������, ����������� � ������������ \f$QR\f$-���������� �������.

  ������������ \f$m\times n\f$ ������� \f$A\f$ ����� \f$n\f$ ���������
  ���������� ���� \f$A=QR\f$, ��� \f$Q\f$ - \f$m\times n\f$ ������� �
  �������������� ���������, \f$R\f$ - ����������������� \f$n\times n\f$
  �������. ����� ���������� ����� ������������ ��� ������� ������� ��������
  ��������� \f$Ax=b\f$, ����� �� � ����������� ������� \f$Rx=Q^{\rm T}b\f$.
  ������ ����������� ������� ��������� ����� ����� ������������� (� ������
  ������ ���������� ���������) ���������������� �������.
  \f$QR\f$-���������� ������������ ����� ��� ���������� ������������������
  ������ ���������������. ���� \f$A\f$ ����� ������ ���������� ����, ��
  ������� ������� \f$Q\f$ ���������� ����������������� �����
  ���������������, ���������� �� ������� ������� \f$A\f$.

\note
  ���� �������� ��� ���� �������. � ������� ���� ��������� ������� � 
  �������� ������� ����������� �������� _t, �� ������� ���� ��������� 
  ������� � ������� ���� �������� _t. ������� ������� ���� ������������,
  ���� �������� ������� ���� ���������������. � ���� ������������ 
  ����������� �����������, ������� ������� ���� �������� ����������� 
  �������, ���� ��������� �� ����������. ������� ��� ������� ������� 
  ������ �������� ��������� � ������� ������ \f$QR\f$-����������, 
  ����������������  ������� ��������������� �������, � ����� ������������ 
  ������� ������� ����.
*/

/**
  \example xqr.c
*/

/**
  \example xqrls.c
*/

/**
  \f$QR\f$-���������� �������.

  ������� ������� \f$QR\f$-���������� \f$m \times n\f$ ������� A �����
  \f$n\f$. �� ������ ��������� � ����������������� ����� ������� \f$A\f$
  �������� �������� ������� \f$R\f$. ������� \f$Q\f$ ������������
  ���������� ���� ��������� � �������� \f$t\f$. ������ \f$t\f$ ����� �����
  \f$n\f$. ������� \f$Q\f$ ������������ ������������� ������ ���������
  �����������: \f$Q = Q_k\cdot\dots\cdot Q_2\cdot Q_1\f$, ��� 
  \f$Q_i=E-t_i v_i v_i^{\rm T}\f$ � \f$v_i=(0,...,1,A_{i+1,i},A_{i+2,i},...,A_{m,i})\f$.
  ����� �� ����� ������������ � ����������� LAPACK, GSL � ��.
  
  ��� ���������� ������������ �������� �������� ����������� (��. [GolubVanLoan],
  �������� 5.2.1).

  - ����:
    - \f$A\f$ - �������, \f$QR\f$-���������� ������� ��������� �����
    - \f$m\f$, \f$n\f$ - ������� ������� A
  - �����:
    - \f$A\f$, \f$t\f$ - ������� � ������, ������� ������ \f$QR\f$-���������� �������� �������

  ������������: \f$2n^2m-(2/3)n^3+O(mn)\f$
*/
extern void qr_decomp(double** A, size_t m, size_t n, double* t);

/**
  \f$QR\f$-���������� �������, � ������� �� #qr_decomp �������� � 
  ����������������� ��������.

  - ����:
    - \f$At\f$ - �������, \f$QR\f$-���������� ������� ��������� �����
    - \f$m\f$, \f$n\f$ - ������� ������� \f$At\f$
  - �����:
    - \f$At\f$, \f$t\f$ - ������� � ������, ������� ������ \f$QR\f$-���������� �������� �������

  ������������: \f$2n^2m-(2/3)n^3+O(mn)\f$
*/
extern void qr_decomp_t(double** At, size_t m, size_t n, double* t);

/**
  ������� ������� �������� ���������.

  ������� ������� ������� ���������� ������� �������� ��������� \f$Ax=b\f$
  ������� \f$n\f$. ������� ���������� �������������� ��������� \f$QR\f$-����������
  ������� \f$A\f$, �������������� �������� \f$QR\f$ � �������� \f$t\f$, ������� ������������
  �������� #qr_decomp. ������� \f$x\f$ ������������ �� ����� ������� ������ �����
  \f$b\f$. ������� \f$QR\f$ � ������ \f$t\f$ �� �������� ������ �������� � ����� ����
  ������������ ��� ������� ������� � ������ ������ ������.

  ������������ �������� ������ � �������� �����������.

  ������������: \f$n^2+O(n)\f$
*/
extern void qr_solve(double** QR, size_t n, double* t, double* b);


/**
  ������� ������� �������� ���������, � ������� �� #qr_solve �������� � 
  ����������������� ��������.

  ������� ������� ������� ���������� ������� �������� ��������� \f$A^Tx=b\f$
  ������� \f$n\f$. ������� ���������� �������������� ��������� \f$QR\f$-����������
  ������� \f$A\f$, �������������� �������� \f$QR\f$ � �������� \f$t\f$, ������� ������������
  �������� #qr_decomp_t. ������� \f$x\f$ ������������ �� ����� ������� ������ �����
  \f$b\f$. ������� \f$QR\f$ � ������ \f$t\f$ �� �������� ������ �������� � ����� ����
  ������������ ��� ������� ������� � ������ ������ ������.

  ������������ �������� ������ � �������� �����������.

  ������������: \f$n^2+O(n)\f$
*/
extern void qr_solve_t(double** QRt, size_t n, double* t, double* b);

/**
  `�������' ���������������� ������� ������� ���������� ���������.

  ������� ������� ������������� ���������������� \f$m \times n\f$ �������
  �������� ��������� \f$Ax=b\f$ ����� \f$n\f$, ��������� ��������������
  ��������� \f$QR\f$-���������� ������� \f$A\f$. \f$QR\f$-���������� ������
  ���� ������������ �������� \f$QR\f$ � �������� \f$t\f$, �������������
  �������� qr_decomp. ������������� ������������ ��������� ����� �������
  \f$\|Ax-b\|_2\f$. ������������� \f$x\f$ ������������ �� ����� ������� ������
  ����� \f$b\f$. ������� \f$Ax-b\f$ ������������ � ������� \f$r\f$.

  ������������: \f$mn+n^2\f$
*/
extern void qr_least_squares(double** QR, size_t m, size_t n, double* t,
  double* b, double* r);


/**
  `�������' ���������������� ������� ������� ���������� ���������, � 
  ������� �� #qr_least_squares �������� � ����������������� ��������.

  ������� ������� ������������� ���������������� \f$m \times n\f$ ������� ��������
  ��������� \f$A^{\rm T}x=b\f$, ��������� �������������� ��������� \f$QR\f$-���������� �������
  \f$A^T\f$. \f$QR\f$-���������� ������ ���� ������������ �������� \f$QR\f$ � �������� \f$t\f$,
  ������������� �������� #qr_decomp_t. ������������� ������������ ���������
  ����� ������� \f$\|A^{\rm T}x-b\|_2\f$. ������������� \f$x\f$ ������������ �� ����� �������
  ������ ����� \f$b\f$. ������� \f$A^{\rm T}x-b\f$ ������������ � ������� \f$r\f$.

  ������������: \f$mn+n^2\f$
*/
extern void qr_least_squares_t(double** QRt, size_t m, size_t n, double* t,
  double* b, double* r);

/**
  ������ ������������� \f$QR\f$-����������.

  ������� ������� ������� \f$Q\f$, \f$R\f$ �������� \f$m \times n\f$ � \f$n\times n\f$ 
  ��������������,
  �������������� � ������������ ������� \f$QR\f$, \f$t\f$.

  ������������: 
*/
extern void qr_least_unpack(double** QR, size_t m, size_t n, double* t,
  double** Q, double** R);

/**
  ������ ������������� \f$QR\f$-����������, � 
  ������� �� #qr_least_unpack �������� � ����������������� ��������.

  ������� ������� ������� Q, R �������� \f$m \times n\f$ � \f$m\times m\f$ ��������������,
  �������������� � ������������ ������� \f$QR\f$, \f$t\f$.

  ������������: 
*/
extern void qr_least_unpack_t(double** QRt, size_t m, size_t n, double* t,
  double** Q, double** R);

#endif

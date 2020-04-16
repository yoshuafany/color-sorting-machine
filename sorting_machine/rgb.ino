int rgb() {
  int merah = read_R();
  int hijau = read_G();
  int biru = read_B();
  if (merah < batas_red2 & merah > batas_red3 & hijau < batas_green2 & hijau > batas_green3 ) {
    color = 2; // biru
  }
  if (merah < batas_blue & merah > batas_blue1 & hijau < batas_green & hijau > batas_green1 ) {
    color = 1; // putih
  }

  return color;
}

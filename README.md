
[![Travis-CI Build
Status](https://travis-ci.org/SymbolixAU/RcppViridis.svg?branch=master)](https://travis-ci.org/SymbolixAU/RcppViridis)
[![Coverage
status](https://codecov.io/gh/SymbolixAU/RcppViridis/branch/master/graph/badge.svg)](https://codecov.io/github/SymbolixAU/RcppViridis?branch=master)
[![Github
Stars](https://img.shields.io/github/stars/SymbolixAU/RcppViridis.svg?style=social&label=Github)](https://github.com/SymbolixAU/RcppViridis)

<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppViridis

-----

### What does it do?

It maps viridis colours to variables, and quickly\!

### Why did you build it?

I’m aware there are other methods for mapping colours to values. And
which do it quick too. But I can never remember them, and I find the
interfaces a bit cumbersome. For example, `scales::col_numeric(palette =
viridisLite::viridis(5), domain = range(1:5))(1:5)`.

I wanted **one** function which will work on **one** argument.

``` r
colour_values(1:5)
# [1] "#440154" "#3B528B" "#21908C" "#5DC963" "#FDE725"
colour_values(letters[1:5])
# [1] "#440154" "#3B528B" "#21908C" "#5DC963" "#FDE725"
```

-----

### Why do you spell colour with a ‘u’?

Because it’s correct, and [R tells us
to](http://developer.r-project.org/Rds.html)

> For consistency, aim to use British (rather than American) spelling

But don’t worry, `color_values(1:5)` works as well

-----

### How do I install it?

Install the development version from
[GitHub](https://github.com/SymbolixAU/RcppViridis) with:

``` r
# install.packages("devtools")
devtools::install_github("SymbolixAU/RcppViridis")
```

-----

<!-- ### How can I make use of it in my package? -->

<!-- **Rcpp** -->

<!-- All functions are written in `Rcpp`. I have exposed some of them in header files so you can `LinkTo` them in your package. -->

<!-- **R** -->

<!-- If you're not using `Rcpp`, just `Import` this package like you would any other.  -->

## Do you have any examples?

Of course\!

#### 256 numbers mapped to a colour

``` r
df <- data.frame(a = 10, x = 1:256)
df$col <- colour_values(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-2-1.png" width="100%" height="200" />

#### 256 numbers on a non-linear scale

``` r
df <- data.frame(a = 10, x = c((1:256)**3))
df$col <- colour_values(df$x, palette = "viridis")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-3-1.png" width="100%" height="200" />

#### 1000 random numbers

``` r
df <- data.frame(a = 10, x = rnorm(n = 1000))
df$col <- colour_values(df$x, palette = "inferno")
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" height="200" />

Eurgh\!

``` r
df <- df[with(df, order(x)), ]
barplot(height = df$a, col = df$col, border = NA, space = 0)
```

<img src="man/figures/README-unnamed-chunk-5-1.png" width="100%" height="200" />

That’s better\!

-----

### What’s the performance like?

**1 million numeric values**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)

n <- 1e6
df <- data.frame(x = rnorm(n = n))

m <- microbenchmark(
  RcppViridis = { RcppViridis::colour_values(x = df$x) },
  scales = { col_numeric(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = range(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 313.6006 329.2112 351.4338 342.7467 354.1284 477.8900    25
#       scales 631.5426 684.7519 732.0164 742.4434 791.0694 837.7403    25

autoplot(m)
```

<img src="man/figures/README-unnamed-chunk-6-1.png" width="100%" height="400" />

**1 million characters (26 unique values)**

``` r
library(microbenchmark)
library(ggplot2)
library(scales)
library(viridisLite)

n <- 1e6
x <- sample(x = letters, size = n, replace = TRUE)
df <- data.frame(x = x)

m <- microbenchmark(
  RcppViridis = { x <- RcppViridis::colour_values(x = df$x) },
  scales = { y <- col_factor(palette = rgb(subset(viridis.map, opt=="D")[, 1:3]), domain = unique(df$x))(df$x) },
  times = 25
)
m
# Unit: milliseconds
#         expr      min       lq     mean   median       uq      max neval
#  RcppViridis 323.0909 348.7706 366.1742 354.0921 364.1317 520.7156    25
#       scales 642.6057 688.9781 745.2099 723.2052 820.0173 870.9324    25

autoplot(m)
```

<img src="man/figures/README-unnamed-chunk-7-1.png" width="100%" height="400" />

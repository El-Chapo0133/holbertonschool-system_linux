#!/bin/sh
# trap signal ABRT IO and TERM
trap "echo Nope" ABRT IO TERM

from pydantic import ValidationError

from zarinpal.models import Wage


def test_valid_wage():
    w = Wage(iban="IR123456789012345678901234", amount=1000, description="Share")
    assert w.amount == 1000


def test_invalid_iban():
    from pytest import raises

    with raises(ValidationError):
        Wage(iban="INVALID", amount=1000, description="x")
